/*
 *      Copyright (c) 1996, 1997 Malcolm Beattie
 *
 *      You may distribute under the terms of either the GNU General Public
 *      License or the Artistic License, as specified in the README file.
 *
 */
/*
 * This file is autogenerated from bytecode.pl. Changes made here will be lost.
 */

#include "EXTERN.h"
#include "perl.h"
#include "bytecode.h"
#include "byterun.h"

#ifdef INDIRECT_BGET_MACROS
void byterun(bs)
struct bytestream bs;
#else
void byterun(fp)
FILE *fp;
#endif /* INDIRECT_BGET_MACROS */
{
    dTHR;
    int insn;
    while ((insn = FGETC()) != EOF) {
	switch (insn) {
	  case INSN_COMMENT:		/* 35 */
	    {
		comment arg;
		BGET_comment(arg);
		arg = arg;
		break;
	    }
	  case INSN_NOP:		/* 10 */
	    {
		break;
	    }
	  case INSN_RET:		/* 0 */
	    {
		BSET_ret(none);
		break;
	    }
	  case INSN_LDSV:		/* 1 */
	    {
		svindex arg;
		BGET_objindex(arg);
		sv = arg;
		break;
	    }
	  case INSN_LDOP:		/* 2 */
	    {
		opindex arg;
		BGET_objindex(arg);
		op = arg;
		break;
	    }
	  case INSN_STSV:		/* 3 */
	    {
		U32 arg;
		BGET_U32(arg);
		BSET_OBJ_STORE(sv, arg);
		break;
	    }
	  case INSN_STOP:		/* 4 */
	    {
		U32 arg;
		BGET_U32(arg);
		BSET_OBJ_STORE(op, arg);
		break;
	    }
	  case INSN_LDSPECSV:		/* 5 */
	    {
		U8 arg;
		BGET_U8(arg);
		BSET_ldspecsv(sv, arg);
		break;
	    }
	  case INSN_NEWSV:		/* 6 */
	    {
		U8 arg;
		BGET_U8(arg);
		BSET_newsv(sv, arg);
		break;
	    }
	  case INSN_NEWOP:		/* 7 */
	    {
		U8 arg;
		BGET_U8(arg);
		BSET_newop(op, arg);
		break;
	    }
	  case INSN_NEWOPN:		/* 8 */
	    {
		U8 arg;
		BGET_U8(arg);
		BSET_newopn(op, arg);
		break;
	    }
	  case INSN_NEWPV:		/* 9 */
	    {
		PV arg;
		BGET_PV(arg);
		break;
	    }
	  case INSN_PV_CUR:		/* 11 */
	    {
		STRLEN arg;
		BGET_U32(arg);
		pv.xpv_cur = arg;
		break;
	    }
	  case INSN_PV_FREE:		/* 12 */
	    {
		BSET_pv_free(pv);
		break;
	    }
	  case INSN_SV_UPGRADE:		/* 13 */
	    {
		char arg;
		BGET_U8(arg);
		BSET_sv_upgrade(sv, arg);
		break;
	    }
	  case INSN_SV_REFCNT:		/* 14 */
	    {
		U32 arg;
		BGET_U32(arg);
		SvREFCNT(sv) = arg;
		break;
	    }
	  case INSN_SV_REFCNT_ADD:		/* 15 */
	    {
		I32 arg;
		BGET_I32(arg);
		BSET_sv_refcnt_add(SvREFCNT(sv), arg);
		break;
	    }
	  case INSN_SV_FLAGS:		/* 16 */
	    {
		U32 arg;
		BGET_U32(arg);
		SvFLAGS(sv) = arg;
		break;
	    }
	  case INSN_XRV:		/* 17 */
	    {
		svindex arg;
		BGET_objindex(arg);
		SvRV(sv) = arg;
		break;
	    }
	  case INSN_XPV:		/* 18 */
	    {
		BSET_xpv(sv);
		break;
	    }
	  case INSN_XIV32:		/* 19 */
	    {
		I32 arg;
		BGET_I32(arg);
		SvIVX(sv) = arg;
		break;
	    }
	  case INSN_XIV64:		/* 20 */
	    {
		IV64 arg;
		BGET_IV64(arg);
		SvIVX(sv) = arg;
		break;
	    }
	  case INSN_XNV:		/* 21 */
	    {
		double arg;
		BGET_double(arg);
		SvNVX(sv) = arg;
		break;
	    }
	  case INSN_XLV_TARGOFF:		/* 22 */
	    {
		STRLEN arg;
		BGET_U32(arg);
		LvTARGOFF(sv) = arg;
		break;
	    }
	  case INSN_XLV_TARGLEN:		/* 23 */
	    {
		STRLEN arg;
		BGET_U32(arg);
		LvTARGLEN(sv) = arg;
		break;
	    }
	  case INSN_XLV_TARG:		/* 24 */
	    {
		svindex arg;
		BGET_objindex(arg);
		LvTARG(sv) = arg;
		break;
	    }
	  case INSN_XLV_TYPE:		/* 25 */
	    {
		char arg;
		BGET_U8(arg);
		LvTYPE(sv) = arg;
		break;
	    }
	  case INSN_XBM_USEFUL:		/* 26 */
	    {
		I32 arg;
		BGET_I32(arg);
		BmUSEFUL(sv) = arg;
		break;
	    }
	  case INSN_XBM_PREVIOUS:		/* 27 */
	    {
		U16 arg;
		BGET_U16(arg);
		BmPREVIOUS(sv) = arg;
		break;
	    }
	  case INSN_XBM_RARE:		/* 28 */
	    {
		U8 arg;
		BGET_U8(arg);
		BmRARE(sv) = arg;
		break;
	    }
	  case INSN_XFM_LINES:		/* 29 */
	    {
		I32 arg;
		BGET_I32(arg);
		FmLINES(sv) = arg;
		break;
	    }
	  case INSN_XIO_LINES:		/* 30 */
	    {
		long arg;
		BGET_I32(arg);
		IoLINES(sv) = arg;
		break;
	    }
	  case INSN_XIO_PAGE:		/* 31 */
	    {
		long arg;
		BGET_I32(arg);
		IoPAGE(sv) = arg;
		break;
	    }
	  case INSN_XIO_PAGE_LEN:		/* 32 */
	    {
		long arg;
		BGET_I32(arg);
		IoPAGE_LEN(sv) = arg;
		break;
	    }
	  case INSN_XIO_LINES_LEFT:		/* 33 */
	    {
		long arg;
		BGET_I32(arg);
		IoLINES_LEFT(sv) = arg;
		break;
	    }
	  case INSN_XIO_TOP_NAME:		/* 34 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		IoTOP_NAME(sv) = arg;
		break;
	    }
	  case INSN_XIO_TOP_GV:		/* 36 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&IoTOP_GV(sv) = arg;
		break;
	    }
	  case INSN_XIO_FMT_NAME:		/* 37 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		IoFMT_NAME(sv) = arg;
		break;
	    }
	  case INSN_XIO_FMT_GV:		/* 38 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&IoFMT_GV(sv) = arg;
		break;
	    }
	  case INSN_XIO_BOTTOM_NAME:		/* 39 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		IoBOTTOM_NAME(sv) = arg;
		break;
	    }
	  case INSN_XIO_BOTTOM_GV:		/* 40 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&IoBOTTOM_GV(sv) = arg;
		break;
	    }
	  case INSN_XIO_SUBPROCESS:		/* 41 */
	    {
		short arg;
		BGET_U16(arg);
		IoSUBPROCESS(sv) = arg;
		break;
	    }
	  case INSN_XIO_TYPE:		/* 42 */
	    {
		char arg;
		BGET_U8(arg);
		IoTYPE(sv) = arg;
		break;
	    }
	  case INSN_XIO_FLAGS:		/* 43 */
	    {
		char arg;
		BGET_U8(arg);
		IoFLAGS(sv) = arg;
		break;
	    }
	  case INSN_XCV_STASH:		/* 44 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&CvSTASH(sv) = arg;
		break;
	    }
	  case INSN_XCV_START:		/* 45 */
	    {
		opindex arg;
		BGET_objindex(arg);
		CvSTART(sv) = arg;
		break;
	    }
	  case INSN_XCV_ROOT:		/* 46 */
	    {
		opindex arg;
		BGET_objindex(arg);
		CvROOT(sv) = arg;
		break;
	    }
	  case INSN_XCV_GV:		/* 47 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&CvGV(sv) = arg;
		break;
	    }
	  case INSN_XCV_FILEGV:		/* 48 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&CvFILEGV(sv) = arg;
		break;
	    }
	  case INSN_XCV_DEPTH:		/* 49 */
	    {
		long arg;
		BGET_I32(arg);
		CvDEPTH(sv) = arg;
		break;
	    }
	  case INSN_XCV_PADLIST:		/* 50 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&CvPADLIST(sv) = arg;
		break;
	    }
	  case INSN_XCV_OUTSIDE:		/* 51 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&CvOUTSIDE(sv) = arg;
		break;
	    }
	  case INSN_XCV_FLAGS:		/* 52 */
	    {
		U8 arg;
		BGET_U8(arg);
		CvFLAGS(sv) = arg;
		break;
	    }
	  case INSN_AV_EXTEND:		/* 53 */
	    {
		SSize_t arg;
		BGET_I32(arg);
		BSET_av_extend(sv, arg);
		break;
	    }
	  case INSN_AV_PUSH:		/* 54 */
	    {
		svindex arg;
		BGET_objindex(arg);
		BSET_av_push(sv, arg);
		break;
	    }
	  case INSN_XAV_FILL:		/* 55 */
	    {
		SSize_t arg;
		BGET_I32(arg);
		AvFILL(sv) = arg;
		break;
	    }
	  case INSN_XAV_MAX:		/* 56 */
	    {
		SSize_t arg;
		BGET_I32(arg);
		AvMAX(sv) = arg;
		break;
	    }
	  case INSN_XAV_FLAGS:		/* 57 */
	    {
		U8 arg;
		BGET_U8(arg);
		AvFLAGS(sv) = arg;
		break;
	    }
	  case INSN_XHV_RITER:		/* 58 */
	    {
		I32 arg;
		BGET_I32(arg);
		HvRITER(sv) = arg;
		break;
	    }
	  case INSN_XHV_NAME:		/* 59 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		HvNAME(sv) = arg;
		break;
	    }
	  case INSN_HV_STORE:		/* 60 */
	    {
		svindex arg;
		BGET_objindex(arg);
		BSET_hv_store(sv, arg);
		break;
	    }
	  case INSN_SV_MAGIC:		/* 61 */
	    {
		char arg;
		BGET_U8(arg);
		BSET_sv_magic(sv, arg);
		break;
	    }
	  case INSN_MG_OBJ:		/* 62 */
	    {
		svindex arg;
		BGET_objindex(arg);
		SvMAGIC(sv)->mg_obj = arg;
		break;
	    }
	  case INSN_MG_PRIVATE:		/* 63 */
	    {
		U16 arg;
		BGET_U16(arg);
		SvMAGIC(sv)->mg_private = arg;
		break;
	    }
	  case INSN_MG_FLAGS:		/* 64 */
	    {
		U8 arg;
		BGET_U8(arg);
		SvMAGIC(sv)->mg_flags = arg;
		break;
	    }
	  case INSN_MG_PV:		/* 65 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		BSET_mg_pv(SvMAGIC(sv), arg);
		break;
	    }
	  case INSN_XMG_STASH:		/* 66 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&SvSTASH(sv) = arg;
		break;
	    }
	  case INSN_GV_FETCHPV:		/* 67 */
	    {
		strconst arg;
		BGET_strconst(arg);
		BSET_gv_fetchpv(sv, arg);
		break;
	    }
	  case INSN_GV_STASHPV:		/* 68 */
	    {
		strconst arg;
		BGET_strconst(arg);
		BSET_gv_stashpv(sv, arg);
		break;
	    }
	  case INSN_GP_SV:		/* 69 */
	    {
		svindex arg;
		BGET_objindex(arg);
		GvSV(sv) = arg;
		break;
	    }
	  case INSN_GP_REFCNT:		/* 70 */
	    {
		U32 arg;
		BGET_U32(arg);
		GvREFCNT(sv) = arg;
		break;
	    }
	  case INSN_GP_REFCNT_ADD:		/* 71 */
	    {
		I32 arg;
		BGET_I32(arg);
		BSET_gp_refcnt_add(GvREFCNT(sv), arg);
		break;
	    }
	  case INSN_GP_AV:		/* 72 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&GvAV(sv) = arg;
		break;
	    }
	  case INSN_GP_HV:		/* 73 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&GvHV(sv) = arg;
		break;
	    }
	  case INSN_GP_CV:		/* 74 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&GvCV(sv) = arg;
		break;
	    }
	  case INSN_GP_FILEGV:		/* 75 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&GvFILEGV(sv) = arg;
		break;
	    }
	  case INSN_GP_IO:		/* 76 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&GvIOp(sv) = arg;
		break;
	    }
	  case INSN_GP_FORM:		/* 77 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&GvFORM(sv) = arg;
		break;
	    }
	  case INSN_GP_CVGEN:		/* 78 */
	    {
		U32 arg;
		BGET_U32(arg);
		GvCVGEN(sv) = arg;
		break;
	    }
	  case INSN_GP_LINE:		/* 79 */
	    {
		line_t arg;
		BGET_U16(arg);
		GvLINE(sv) = arg;
		break;
	    }
	  case INSN_GP_SHARE:		/* 80 */
	    {
		svindex arg;
		BGET_objindex(arg);
		BSET_gp_share(sv, arg);
		break;
	    }
	  case INSN_XGV_FLAGS:		/* 81 */
	    {
		U8 arg;
		BGET_U8(arg);
		GvFLAGS(sv) = arg;
		break;
	    }
	  case INSN_OP_NEXT:		/* 82 */
	    {
		opindex arg;
		BGET_objindex(arg);
		op->op_next = arg;
		break;
	    }
	  case INSN_OP_SIBLING:		/* 83 */
	    {
		opindex arg;
		BGET_objindex(arg);
		op->op_sibling = arg;
		break;
	    }
	  case INSN_OP_PPADDR:		/* 84 */
	    {
		strconst arg;
		BGET_strconst(arg);
		BSET_op_ppaddr(op->op_ppaddr, arg);
		break;
	    }
	  case INSN_OP_TARG:		/* 85 */
	    {
		PADOFFSET arg;
		BGET_U32(arg);
		op->op_targ = arg;
		break;
	    }
	  case INSN_OP_TYPE:		/* 86 */
	    {
		OPCODE arg;
		BGET_U16(arg);
		BSET_op_type(op, arg);
		break;
	    }
	  case INSN_OP_SEQ:		/* 87 */
	    {
		U16 arg;
		BGET_U16(arg);
		op->op_seq = arg;
		break;
	    }
	  case INSN_OP_FLAGS:		/* 88 */
	    {
		U8 arg;
		BGET_U8(arg);
		op->op_flags = arg;
		break;
	    }
	  case INSN_OP_PRIVATE:		/* 89 */
	    {
		U8 arg;
		BGET_U8(arg);
		op->op_private = arg;
		break;
	    }
	  case INSN_OP_FIRST:		/* 90 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cUNOP->op_first = arg;
		break;
	    }
	  case INSN_OP_LAST:		/* 91 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cBINOP->op_last = arg;
		break;
	    }
	  case INSN_OP_OTHER:		/* 92 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cLOGOP->op_other = arg;
		break;
	    }
	  case INSN_OP_TRUE:		/* 93 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cCONDOP->op_true = arg;
		break;
	    }
	  case INSN_OP_FALSE:		/* 94 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cCONDOP->op_false = arg;
		break;
	    }
	  case INSN_OP_CHILDREN:		/* 95 */
	    {
		U32 arg;
		BGET_U32(arg);
		cLISTOP->op_children = arg;
		break;
	    }
	  case INSN_OP_PMREPLROOT:		/* 96 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cPMOP->op_pmreplroot = arg;
		break;
	    }
	  case INSN_OP_PMREPLROOTGV:		/* 97 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&cPMOP->op_pmreplroot = arg;
		break;
	    }
	  case INSN_OP_PMREPLSTART:		/* 98 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cPMOP->op_pmreplstart = arg;
		break;
	    }
	  case INSN_OP_PMNEXT:		/* 99 */
	    {
		opindex arg;
		BGET_objindex(arg);
		*(OP**)&cPMOP->op_pmnext = arg;
		break;
	    }
	  case INSN_PREGCOMP:		/* 100 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		BSET_pregcomp(op, arg);
		break;
	    }
	  case INSN_OP_PMFLAGS:		/* 101 */
	    {
		U16 arg;
		BGET_U16(arg);
		cPMOP->op_pmflags = arg;
		break;
	    }
	  case INSN_OP_PMPERMFLAGS:		/* 102 */
	    {
		U16 arg;
		BGET_U16(arg);
		cPMOP->op_pmpermflags = arg;
		break;
	    }
	  case INSN_OP_SV:		/* 103 */
	    {
		svindex arg;
		BGET_objindex(arg);
		cSVOP->op_sv = arg;
		break;
	    }
	  case INSN_OP_GV:		/* 104 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&cGVOP->op_gv = arg;
		break;
	    }
	  case INSN_OP_PV:		/* 105 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		cPVOP->op_pv = arg;
		break;
	    }
	  case INSN_OP_PV_TR:		/* 106 */
	    {
		op_tr_array arg;
		BGET_op_tr_array(arg);
		cPVOP->op_pv = arg;
		break;
	    }
	  case INSN_OP_REDOOP:		/* 107 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cLOOP->op_redoop = arg;
		break;
	    }
	  case INSN_OP_NEXTOP:		/* 108 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cLOOP->op_nextop = arg;
		break;
	    }
	  case INSN_OP_LASTOP:		/* 109 */
	    {
		opindex arg;
		BGET_objindex(arg);
		cLOOP->op_lastop = arg;
		break;
	    }
	  case INSN_COP_LABEL:		/* 110 */
	    {
		pvcontents arg;
		BGET_pvcontents(arg);
		cCOP->cop_label = arg;
		break;
	    }
	  case INSN_COP_STASH:		/* 111 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&cCOP->cop_stash = arg;
		break;
	    }
	  case INSN_COP_FILEGV:		/* 112 */
	    {
		svindex arg;
		BGET_objindex(arg);
		*(SV**)&cCOP->cop_filegv = arg;
		break;
	    }
	  case INSN_COP_SEQ:		/* 113 */
	    {
		U32 arg;
		BGET_U32(arg);
		cCOP->cop_seq = arg;
		break;
	    }
	  case INSN_COP_ARYBASE:		/* 114 */
	    {
		I32 arg;
		BGET_I32(arg);
		cCOP->cop_arybase = arg;
		break;
	    }
	  case INSN_COP_LINE:		/* 115 */
	    {
		line_t arg;
		BGET_U16(arg);
		cCOP->cop_line = arg;
		break;
	    }
	  case INSN_MAIN_START:		/* 116 */
	    {
		opindex arg;
		BGET_objindex(arg);
		main_start = arg;
		break;
	    }
	  case INSN_MAIN_ROOT:		/* 117 */
	    {
		opindex arg;
		BGET_objindex(arg);
		main_root = arg;
		break;
	    }
	  case INSN_CURPAD:		/* 118 */
	    {
		svindex arg;
		BGET_objindex(arg);
		BSET_curpad(curpad, arg);
		break;
	    }
	  default:
	    croak("Illegal bytecode instruction %d\n", insn);
	    /* NOTREACHED */
	}
    }
}
