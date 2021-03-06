/*	SCCS Id: @(#)monst.h	3.4	1999/01/04	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef MONST_H
#define MONST_H

/* The weapon_check flag is used two ways:
 * 1) When calling mon_wield_item, is 2-6 depending on what is desired.
 * 2) Between calls to mon_wield_item, is 0 or 1 depending on whether or not
 *    the weapon is known by the monster to be cursed (so it shouldn't bother
 *    trying for another weapon).
 * I originally planned to also use 0 if the monster already had its best
 * weapon, to avoid the overhead of a call to mon_wield_item, but it turns out
 * that there are enough situations which might make a monster change its
 * weapon that this is impractical.  --KAA
 */
# define NO_WEAPON_WANTED 0
# define NEED_WEAPON 1
# define NEED_RANGED_WEAPON 2
# define NEED_HTH_WEAPON 3
# define NEED_PICK_AXE 4
# define NEED_AXE 5
# define NEED_PICK_OR_AXE 6

/* The following flags are used for the second argument to display_minventory
 * in invent.c:
 *
 * MINV_NOLET  If set, don't display inventory letters on monster's inventory.
 * MINV_ALL    If set, display all items in monster's inventory, otherwise
 *	       just display wielded weapons and worn items.
 */
#define MINV_NOLET 0x01
#define MINV_ALL   0x02

#ifndef ALIGN_H
#include "align.h"
#endif

struct monst {
	struct monst *nmon;
	struct permonst *data;
	unsigned m_id;
	int mnum;		/* permanent monster index number */
	short movement;		/* movement points (derived from permonst definition and added effects */
	uchar m_lev;		/* adjusted difficulty level of monster */
	aligntyp malign;	/* alignment of this monster, relative to the
				   player (positive = good to kill) */
	xchar mx, my;
	xchar mux, muy;		/* where the monster thinks you are */
#define MTSZ	4
	coord mtrack[MTSZ];	/* monster track */
	int mhp, mhpmax;
	unsigned mappearance;	/* for undetected mimics and the wiz */
	uchar	 m_ap_type;	/* what mappearance is describing: */
#define M_AP_NOTHING	0	/* mappearance is unused -- monster appears
				   as itself */
#define M_AP_FURNITURE	1	/* stairs, a door, an altar, etc. */
#define M_AP_OBJECT	2	/* an object */
#define M_AP_MONSTER	3	/* a monster */

	int mtame;		/* level of tameness, implies peaceful */
	int mpeacetime;		/* level of peacefulness, implies peaceful, ignored if tame */
	unsigned int mintrinsics;	/* low 10 correspond to mresists */
	int mspec_used;		/* monster's special ability attack timeout */
	int mstdy;		/* to record extra damage to be delt due to having been studied */
	int ustdym;		/* to record extra damage to be delt by you due to having been studied by you*/

	Bitfield(mferal,1);	/* was once tame */
	
	Bitfield(female,1);	/* is female */
	Bitfield(minvis,1);	/* currently invisible */
	Bitfield(invis_blkd,1); /* invisibility blocked */
	Bitfield(perminvis,1);	/* intrinsic minvis value */
	Bitfield(cham,4);	/* shape-changer */
/* note: lychanthropes are handled elsewhere */
#define CHAM_ORDINARY		0	/* not a shapechanger */
#define CHAM_CHAMELEON		1	/* animal */
#define CHAM_DOPPELGANGER	2	/* demi-human */
#define CHAM_SANDESTIN		3	/* demon */
#define CHAM_DREAM			4	/* anything */
#define CHAM_MAX_INDX		CHAM_DREAM
	Bitfield(mundetected,1);	/* not seen in present hiding place */
				/* implies one of M1_CONCEAL or M1_HIDE,
				 * but not mimic (that is, snake, spider,
				 * trapper, piercer, eel)
				 */

	Bitfield(mcan,1);	/* has been cancelled */
	Bitfield(mburied,1);	/* has been buried */
	Bitfield(mspeed,2);	/* current speed */
	Bitfield(permspeed,2);	/* intrinsic mspeed value */
	Bitfield(mrevived,1);	/* has been revived from the dead */
	Bitfield(mavenge,1);	/* did something to deserve retaliation */
	
	Bitfield(mflee,1);	/* fleeing */
	Bitfield(mfleetim,7);	/* timeout for mflee */
	
	Bitfield(mcrazed,1);	/* monster is crazed */
	
	Bitfield(mberserk,1);	/* monster is crazed */
	
	Bitfield(mcansee,1);	/* cansee 1, temp.blinded 0, blind 0 */
	Bitfield(mblinded,7);	/* cansee 0, temp.blinded n, blind 0 */

	Bitfield(mcanmove,1);	/* paralysis, similar to mblinded */
	Bitfield(mfrozen,7);
	
	Bitfield(mnotlaugh,1);	/* collapsed from laughter, similar to mblinded */
	Bitfield(mlaughing,7);
	
	Bitfield(msleeping,1);	/* asleep until woken */
	Bitfield(mstun,1);	/* stunned (off balance) */
	Bitfield(mconf,1);	/* confused */
	Bitfield(mpeaceful,1);	/* does not attack unprovoked */
	Bitfield(mtrapped,1);	/* trapped in a pit, web or bear trap */
	Bitfield(mleashed,1);	/* monster is on a leash */
	Bitfield(mtraitor,1);	/* Former pet that turned traitor */
	Bitfield(isshk,1);	/* is shopkeeper */
	Bitfield(isminion,1);	/* is a minion */
	
	Bitfield(isgd,1);	/* is guard */
	Bitfield(ispriest,1);	/* is a priest */
	Bitfield(iswiz,1);	/* is the Wizard of Yendor */
	Bitfield(wormno,5);	/* at most 31 worms on any level */
#define MAX_NUM_WORMS	32	/* should be 2^(wormno bitfield size) */
	Bitfield(moccupation,1);/* linked to your occupation */
	Bitfield(mclone,1);		/* is a clone of another monster (don't make death drop) */
	Bitfield(uhurtm,1);		/* injured by you */
	Bitfield(mhurtu,1);		/* has injured you */
	Bitfield(mattackedu,1);	/* attacked you on it's last turn */
	Bitfield(housealert,1);	/* won't accept house-based pacification */
	Bitfield(mspiritual,1);	/* Created by spirit power, doesn't count towards pet limit */
#define BASE_DOG_ENCOURAGED_MAX		7
	int encouraged;	/* affected by Encourage song */
#define helpless(mon) (mon->msleeping || !(mon->mcanmove) || !(mon->mnotlaugh))	
	
	long mstrategy;		/* for monsters with mflag3: current strategy */
#define STRAT_ARRIVE	0x40000000L	/* just arrived on current level */
#define STRAT_WAITFORU	0x20000000L
#define STRAT_CLOSE	0x10000000L
#define STRAT_WAITMASK	0x30000000L
#define STRAT_HEAL	0x08000000L
#define STRAT_GROUND	0x04000000L
#define STRAT_MONSTR	0x02000000L
#define STRAT_PLAYER	0x01000000L
#define STRAT_NONE	0x00000000L
#define STRAT_STRATMASK 0x0f000000L
#define STRAT_XMASK	0x00ff0000L
#define STRAT_YMASK	0x0000ff00L
#define STRAT_GOAL	0x000000ffL
#define STRAT_GOALX(s)	((xchar)((s & STRAT_XMASK) >> 16))
#define STRAT_GOALY(s)	((xchar)((s & STRAT_YMASK) >> 8))

	long mtrapseen;		/* bitmap of traps we've been trapped in */
	long mlstmv;		/* for catching up with lost time */
#ifndef GOLDOBJ
	long mgold;
#endif
	struct obj *minvent;

	struct obj *mw;
	long misc_worn_check;
	xchar weapon_check;
	xchar combat_mode;
#define	RANGED_MODE	0
#define HNDHND_MODE	1

	uchar mnamelth;		/* length of name (following mxlth) */
	short mxlth;		/* length of following data */
	int meating;		/* monster is eating timeout */
	int mfaction;		/* faction to which monster belongs */
	int mvanishes;
	//hatching situation
	//AT_LAYEGG, PM_HATCHLING_NAME, x, d
	//timetohatch
	//larvatime (larva effects default or by hatchling, time default or by hatchling)
	//	time:  AT_LARVA+x, where x=time, and AT_LARVA is large, 10000 or so.
	//utype = PM_HATCHLING_NAME
	//inventory
	long mvar1;
	long mvar2;
	long mvar3;
	/* in order to prevent alignment problems mextra should
	   be (or follow) a long int */
	long mextra[1]; /* monster dependent info */
};

/*
 * Note that mextra[] may correspond to any of a number of structures, which
 * are indicated by some of the other fields.
 *	isgd	 ->	struct egd
 *	ispriest ->	struct epri
 *	isshk	 ->	struct eshk
 *	isminion ->	struct emin
 *			(struct epri for roaming priests and angels, which is
 *			 compatible with emin for polymorph purposes)
 *	mtame	 ->	struct edog
 *			(struct epri for guardian angels, which do not eat
 *			 or do other doggy things)
 * Since at most one structure can be indicated in this manner, it is not
 * possible to tame any creatures using the other structures (the only
 * exception being the guardian angels which are tame on creation).
 */

#define newmonst(xl) (struct monst *)alloc((unsigned)(xl) + sizeof(struct monst))
#define dealloc_monst(mon) free((genericptr_t)(mon))

/* these are in mspeed */
#define MSLOW 1		/* slow monster */
#define MFAST 2		/* speeded monster */

#define NAME(mtmp)	(((char *)(mtmp)->mextra) + (mtmp)->mxlth)

#define MON_WEP(mon)	((mon)->mw)
#define MON_NOWEP(mon)	((mon)->mw = (struct obj *)0)

#define DEADMONSTER(mon)	((mon)->mhp < 1)

#endif /* MONST_H */
