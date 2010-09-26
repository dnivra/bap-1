/*
 Owned and copyright BitBlaze, 2007. All rights reserved.
 Do not copy, disclose, or distribute without explicit written
 permission.
*/
#ifndef _ASM_PROGRAM_H
#define _ASM_PROGRAM_H


#ifdef __cplusplus
extern "C"
{
#endif

// from binutils
#include <bfd.h>
#include <dis-asm.h>

#include "common.h"

#define MAX_INSN_BYTES 15
  
typedef struct section
{
  bfd_byte *data;
  bfd_size_type datasize;
  
  bfd_vma start_addr; // first byte in the segment
  bfd_vma end_addr; // first byte after the segment

  asection *section;
  int is_code;

  struct section *next;
} section_t;



typedef struct asm_program {
  char *name;
  bfd *abfd;
  struct disassemble_info disasm_info;
  section_t *segs; // linked list of segments
} asm_program_t;

extern asm_program_t *asmir_open_file(const char *filename);
extern asm_program_t* asmir_new_asmp_for_arch(enum bfd_architecture arch);
extern void asmir_close(asm_program_t *p);
extern bfd_byte *asmir_get_ptr_to_instr(asm_program_t *prog, bfd_vma addr);
extern int asmir_get_instr_length(asm_program_t *prog, bfd_vma addr);

// helper for disassembling bytes in traces
extern void set_trace_bytes(void *bytes, size_t len, bfd_vma addr);
  
// dissassemble an instruction and return the asm string
extern char* asmir_string_of_insn(asm_program_t *prog, bfd_vma inst);


#ifdef __cplusplus
}
#endif


// pulled from disasm.h
#ifndef bfd_get_section_size_before_reloc
#define bfd_get_section_size_before_reloc(x) bfd_get_section_size(x)
#endif



#endif
