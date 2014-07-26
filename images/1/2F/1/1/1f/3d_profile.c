/*
 *  3d_profile.h
 *  
 *
 *  Created by Administrator on 4/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#include "udf.h"
#include <math.h>
#define U0 2.486      /* Maximum inlet velocity [m/s]                 */
#define RP 0.00025    /* Pipe radius [m]                              */
#define NO_BUBBLES 1  /* numbers of bubbles currently limited to 3     */
#define FLOW_DIRECTION 1 /* for x direction 1, for y direction 2, and for z 3 */
DEFINE_PROFILE(velocity_profile,thread,index)
{
#if !RP_HOST
#if FLOW_DIRECTION==1
	real x[ND_ND]; /* this will hold the position vector */
	real y,z;
	face_t f;
	
	/* loops over all faces in the thread */
	begin_f_loop(f,thread)
	{
		F_CENTROID(x,f,thread);
		y = x[1];
		z = x[2];
		F_PROFILE(f,thread,index) = U0*(1.0-(y*y+z*z)/(RP*RP));
	}
	end_f_loop(f,thread)
#elif FLOW_DIRECTION==2
	real y[ND_ND]; /* this will hold the position vector */
	real x,z;
	face_t f;
	
	/* loops over all faces in the thread */
	begin_f_loop(f,thread)
	{
		F_CENTROID(y,f,thread);
		x = y[0];
		z = y[2];
		F_PROFILE(f,thread,index) = U0*(1.0-(x*x+z*z)/(RP*RP));
	}
	end_f_loop(f,thread)
#elif FLOW_DIRECTION==3
	real z[ND_ND]; /* this will hold the position vector */
	real x,y;
	face_t f;
	
	/* loops over all faces in the thread */
	begin_f_loop(f,thread)
	{
		F_CENTROID(z,f,thread);
		x = z[0];
		y = z[1];
		F_PROFILE(f,thread,index) = U0*(1.0-(x*x+y*y)/(RP*RP));
	}
	end_f_loop(f,thread)
#else
	Error("FLOW_DIRECTION should be 1, 2 or 3");
#endif /* FLOW_DIRECTION */
#endif /* RP_HOST */
}


