/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "lib/xalloc.h"
#include "lib/stack.h"
#include "lib/contracts.h"
#include "lib/c0v_stack.h"
#include "lib/c0vm.h"
#include "lib/c0vm_c0ffi.h"
#include "lib/c0vm_abort.h"

/* call stack frames */
typedef struct frame_info frame;
struct frame_info {
  c0v_stack_t  S;   /* Operand stack of C0 values */
  ubyte       *P;   /* Function body */
  size_t       pc;  /* Program counter */
  c0_value    *V;   /* The local variables */
};

void push_int(c0v_stack_t S, int32_t i) {
  c0v_push(S, int2val(i));
}

void push_ptr(c0v_stack_t S, void *p) {
  c0v_push(S, ptr2val(p));
}

int32_t pop_int(c0v_stack_t S) {
  return val2int(c0v_pop(S));
}

void *pop_ptr(c0v_stack_t S) {
  return val2ptr(c0v_pop(S));
}

int execute(struct bc0_file *bc0) {
  REQUIRES(bc0 != NULL);

  /* Variables */
  c0v_stack_t S = c0v_stack_new();             /* Operand stack of C0 values */
  ubyte *P = bc0->function_pool[0].code;       /* Array of bytes that make up the current function */
  size_t pc = 0;                               /* Current location within the current byte array P */
  c0_value *V = xmalloc(sizeof(c0_value)*bc0->function_pool[0].num_vars);   /* Local variables */
  // (void) V;      // silences compilation errors about V being currently unused

  /* The call stack, a generic stack that should contain pointers to frames */
  /* You won't need this until you implement functions. */
  gstack_t callStack = stack_new();
  // (void) callStack; // silences compilation errors about callStack being currently unused

  while (true) {

#ifdef DEBUG
    /* You can add extra debugging information here */
    fprintf(stderr, "Opcode %x -- Stack size: %zu -- PC: %zu\n",
            P[pc], c0v_stack_size(S), pc);
#endif

    switch (P[pc]) {

    /* Additional stack operation: */

    case POP: {
      pc++;
      c0v_pop(S);
      break;
    }

    case DUP: {
      pc++;
      c0_value v = c0v_pop(S);
      c0v_push(S,v);
      c0v_push(S,v);
      break;
    }

    case SWAP: {
      c0_value x = c0v_pop(S);
      c0_value y = c0v_pop(S);
      c0v_push(S,x);
      c0v_push(S,y);
      pc++;
      break;
    }

    /* Returning from a function.
     * This currently has a memory leak! You will need to make a slight
     * change for the initial tasks to avoid leaking memory.  You will
     * need to revise it further when you write INVOKESTATIC. */

    case RETURN: {
      if (stack_empty(callStack)) { // main function return
        int retval = val2int(c0v_pop(S));
        ASSERT(c0v_stack_empty(S));
        // Another way to print only in DEBUG mode
        IF_DEBUG(fprintf(stderr, "Returning %d from execute()\n", retval));
        // Free everything before returning from the execute function!
        c0v_stack_free(S);
        stack_free(callStack, NULL);
        free(V);
        return retval;
      }
      frame *oldF = (frame*)pop(callStack);
      c0v_push(oldF->S, c0v_pop(S)); // pop returned value back
      ASSERT(c0v_stack_empty(S));
      free(V);
      c0v_stack_free(S);
      S = oldF->S;
      V = oldF->V;
      pc = oldF->pc;
      P = oldF->P;
      free(oldF);
      break;
    }

    /* Arithmetic and Logical operations */

    case IADD: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      push_int(S,x+y);
      pc++;
      break; 
    }

    case ISUB: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      push_int(S,x-y);
      pc++;
      break;
    }

    case IMUL: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      push_int(S,x*y);
      pc++;
      break;
    }

    case IDIV: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      if (y==0) {
        c0_arith_error("Division by 0");
      } else if (x==-2147483648 && y==-1) {
        c0_arith_error("Division causes overflow");
      }
      push_int(S,x/y);
      pc++;
      break;
    }

    case IREM: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      if (y==0) {
        c0_arith_error("Modulo by 0");
      } else if (x==-2147483648 && y==-1) {
        c0_arith_error("Modulo causes overflow");
      }
      push_int(S,x%y);
      pc++;
      break;
    }

    case IAND: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      push_int(S,x&y);
      pc++;
      break;
    }

    case IOR: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      push_int(S,x|y);
      pc++;
      break;
    }

    case IXOR: {
      int32_t y = pop_int(S);
      int32_t x = pop_int(S);
      push_int(S,x^y);
      pc++;
      break;
    }

    case ISHR: {
      int32_t y = pop_int(S);
      if (y<0 || y>=32)
        c0_arith_error("Shift right out-of-range");
      int32_t x = pop_int(S);
      push_int(S,x>>y);
      pc++;
      break;
    }

    case ISHL: {
      int32_t y = pop_int(S);
      if (y<0 || y>=32)
        c0_arith_error("Shift left out-of-range");
      int32_t x = pop_int(S);
      push_int(S,x<<y);
      pc++;
      break;
    }

    /* Pushing constants */

    case BIPUSH: {
      push_int(S,(int32_t)(int8_t)P[pc+1]); // cast ubyte to sign then to 32
      pc += 2;
      break;
    }

    case ILDC: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t c = c1<<8|c2;
      ASSERT(c<bc0->int_count);
      int x = bc0->int_pool[c];
      push_int(S,x);
      pc+=3;
      break;
    }

    case ALDC: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t c = c1<<8|c2;
      ASSERT(c<bc0->string_count);
      char *a = &(bc0->string_pool[c]);
      push_ptr(S, (void*)a);
      pc+=3;
      break;
    }

    case ACONST_NULL: {
      push_ptr(S, NULL);
      pc++;
      break;
    }

    /* Operations on local variables */

    case VLOAD: {
      ubyte i = P[pc+1];
      // ASSERT(i<\length(V));
      c0v_push(S, V[i]);
      pc+=2;
      break;
    }

    case VSTORE: {
      ubyte i = P[pc+1];
      // ASSERT(i<\length(V));
      V[i] = c0v_pop(S);
      pc+=2;
      break;
    }

    /* Assertions and errors */

    case ATHROW: {
      void *p = pop_ptr(S);
      if (p==NULL)
        c0_memory_error("Deference NULL pointer");
      c0_user_error((char*)p);
      pc++;
      break;
    }

    case ASSERT: {
      void *p = pop_ptr(S);
      if (p==NULL)
        c0_memory_error("Deference NULL pointer");
      int32_t x = pop_int(S);
      if (x==0)
        c0_assertion_failure((char*)p);
      pc++;
      break;
    }

    /* Control flow operations */

    case NOP: {
      break;
    }

    case IF_CMPEQ: {
      c0_value y = c0v_pop(S);
      c0_value x = c0v_pop(S);
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      if (val_equal(x,y)) {
        pc += offset;
      } else {
        pc += 3;
      }
      break;
    }

    case IF_CMPNE: {
      c0_value y = c0v_pop(S);
      c0_value x = c0v_pop(S);
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      if (!val_equal(x,y)) {
        pc += offset;
      } else {
        pc += 3;
      }
      break;
    }

    case IF_ICMPLT: {
      int32_t y =  pop_int(S);
      int32_t x = pop_int(S);
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      if (x<y) {
        pc += offset;
      } else {
        pc += 3;
      }
      break;
    }

    case IF_ICMPGE: {
      int32_t y =  pop_int(S);
      int32_t x = pop_int(S);
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      if (x>=y) {
        pc += offset;
      } else {
        pc += 3;
      }
      break;
    }

    case IF_ICMPGT: {
      int32_t y =  pop_int(S);
      int32_t x = pop_int(S);
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      if (x>y) {
        pc += offset;
      } else {
        pc += 3;
      }
      break;
    }

    case IF_ICMPLE: {
      int32_t y =  pop_int(S);
      int32_t x = pop_int(S);
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      if (x<=y) {
        pc += offset;
      } else {
        pc += 3;
      }
      break;
    }

    case GOTO: {
      uint16_t o2 = (uint16_t)P[pc+2];
      int16_t o1 = (int16_t)P[pc+1];
      int16_t offset = o1<<8|o2;
      pc += offset;
      break;
    }

    /* Function call operations: */

    case INVOKESTATIC: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t c = c1<<8|c2;
      struct function_info newF = bc0->function_pool[c];
      c0_value *newV = xmalloc(sizeof(c0_value)*newF.num_vars);
      for (uint16_t i=newF.num_args; i>0; i--)
        newV[i-1] = c0v_pop(S);
      // newV[0] = c0v_pop(S);
      frame *oldFrame = xmalloc(sizeof(frame));
      oldFrame->P = P;
      oldFrame->V = V;
      oldFrame->S = S;
      oldFrame->pc = pc+3;
      push(callStack, (void*)oldFrame);

      V = newV;
      S = c0v_stack_new();
      pc = 0;
      P = newF.code;
      break;
    }

    case INVOKENATIVE: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t c = c1<<8|c2;
      struct native_info naF = bc0->native_pool[c];
      c0_value *args = xmalloc(sizeof(c0_value)*naF.num_args);
      for (uint16_t i=naF.num_args; i>0; i--)
        args[i-1] = c0v_pop(S);
      // args[0] = c0v_pop(S);
      native_fn *g = native_function_table[naF.function_table_index];
      c0v_push(S,(*g)(args));
      free(args);
      pc += 3;
      break;
    }

    /* Memory allocation and access operations: */

    case NEW: {
      void *p = xcalloc(1,P[pc+1]); // calloc !!
      push_ptr(S, p);
      pc += 2;
      break;
    }

    case IMLOAD: {
      void *p = pop_ptr(S);
      if (p==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      int32_t x = *(int*)p;
      push_int(S, x);
      pc++;
      break;
    }

    case IMSTORE: {
      int32_t x = pop_int(S);
      int *p = (int*)pop_ptr(S);
      if (p==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      *p = x;
      pc++;
      break;
    }

    case AMLOAD: {
      void **p = (void**)pop_ptr(S); // void ** !!
      if (p==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      push_ptr(S, *p);
      pc++;
      break;
    }

    case AMSTORE: {
      void *b = pop_ptr(S);
      void **a = (void**)pop_ptr(S); // void ** !!
      if (a==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      *a = b;
      pc++;
      break;
    }

    case CMLOAD: {
      char *p = (char*)pop_ptr(S);
      if (p==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      push_int(S, (int32_t)*p);
      pc++;
      break;
    }

    case CMSTORE: {
      int32_t x = pop_int(S);
      char *p = (char*)pop_ptr(S);
      if (p==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      *p = x&0x7f; // result is 7 bits
      pc++;
      break;
    }

    case AADDF: { // struct
      void *a = pop_ptr(S);
      if (a==NULL)
        c0_memory_error("Attempt to dereference null pointer");
      push_ptr(S, (void*)((char*)a+P[pc+1]));
      /* cast void* to char* then add
      = A + i, since A is char*, so +i = +i byte
      and we want to + P[pc+1] bytes */
      pc += 2;
      break;
    }

    /* Array operations: */

    case NEWARRAY: {
      int32_t n = pop_int(S);
      if (n<0)
        c0_memory_error("Array size cannot be negative");
      if (n==0) { // empty array
        push_ptr(S, NULL);
        pc += 2;
        break;
      }
      ubyte s = P[pc+1];
      c0_array *A = xmalloc(sizeof(c0_array));
      A->count = (uint32_t)n; // n not negative, so cast will retain value
      A->elt_size = (uint32_t)s;
      A->elems = xcalloc(n, s); // calloc !!
      push_ptr(S, (void*)A);
      pc += 2;
      break;
    }

    case ARRAYLENGTH: {
      c0_array *A = (c0_array*)pop_ptr(S);
      if (A==NULL) {
        push_int(S, 0);
        pc++;
        break;
      }
      push_int(S, (int32_t)A->count);
      pc++;
      break;
    }

    case AADDS: {
      int32_t i_int = pop_int(S);
      if (i_int<0)
        c0_memory_error("Array index out of bounds");
      uint32_t i = (uint32_t)i_int; // i_int is not negative
      c0_array *A = (c0_array*)pop_ptr(S);
      if (i >= A->count)
        c0_memory_error("Array index out of bounds");
      char *arr = (char*)A->elems;
      push_ptr(S, (void*)(arr+i*A->elt_size));
      pc++;
      break;
    }

    /* BONUS -- C1 operations */

    case CHECKTAG: {
      c0_tagged_ptr *gp = val2tagged_ptr(c0v_pop(S));
      if (gp==NULL) {
        push_ptr(S, NULL);
        // free(gp);
        pc += 3;
        break;
      }
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t tag = c1<<8|c2;
      ASSERT(gp!=NULL);
      if (gp->tag!=tag) 
        c0_memory_error("Pointer's tag mismatch");
      push_ptr(S,gp->p);
      // free(gp);
      pc += 3;
      break;
    }

    case HASTAG: {
      c0_tagged_ptr *gp = val2tagged_ptr(c0v_pop(S));
      if (gp==NULL) {
        push_int(S,1);
        // free(gp);
        pc += 3;
        break;
      }
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t tag = c1<<8|c2;
      if (gp->tag!=tag) {
        push_int(S,0);
      } else {
        push_int(S,1);
      }
      // free(gp);
      pc += 3;
      break;
    }

    case ADDTAG: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t tag = c1<<8|c2;
      void *p = pop_ptr(S);
      c0v_push(S, tagged_ptr2val(p,tag));
      pc += 3;
      break;
    }

    case ADDROF_STATIC: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t c = c1<<8|c2;
      void *fp = create_funptr(false, c);
      push_ptr(S,fp);
      pc += 3;
      break;
    }

    case ADDROF_NATIVE: {
      uint16_t c2 = (uint16_t)P[pc+2];
      uint16_t c1 = (uint16_t)P[pc+1];
      uint16_t c = c1<<8|c2;
      void *fp = create_funptr(true, c);
      push_ptr(S,fp);
      pc += 3;
      break;
    }

    case INVOKEDYNAMIC: {
      void *fp = pop_ptr(S);
      uint16_t index = funptr2index(fp);
      if (is_native_funptr(fp)) { // native
        struct native_info naF = bc0->native_pool[index];
        c0_value *args = xmalloc(sizeof(c0_value)*naF.num_args);
        for (uint16_t i=naF.num_args; i>0; i--)
          args[i-1] = c0v_pop(S);
        native_fn *g = native_function_table[naF.function_table_index];
        c0v_push(S,(*g)(args));
        free(args);
        pc++;
      } else {
        struct function_info newF = bc0->function_pool[index];
        c0_value *newV = xmalloc(sizeof(c0_value)*newF.num_vars);
        for (uint16_t i=newF.num_args; i>0; i--)
          newV[i-1] = c0v_pop(S);
        frame *oldFrame = xmalloc(sizeof(frame));
        oldFrame->P = P;
        oldFrame->V = V;
        oldFrame->S = S;
        pc++;
        oldFrame->pc = pc; // cannot be pc++, it returns pc
        push(callStack, (void*)oldFrame);

        V = newV;
        S = c0v_stack_new();
        pc = 0;
        P = newF.code;
      }
      break;
    }

    default:
      fprintf(stderr, "invalid opcode: 0x%02x\n", P[pc]);
      abort();
    }
  }

  /* cannot get here from infinite loop */
  assert(false);
}