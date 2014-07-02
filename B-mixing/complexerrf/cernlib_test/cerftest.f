C--------------------------------------------------------------
C.....A PROGRAM TO TEST THE CERNLIB COMPLEX ERROR FUNCTION.....
C--------------------------------------------------------------

      PROGRAM CERFTEST

      
C.....DECLARE OUR COMPLEX ARGUMENTS:

      COMPLEX*16 ARGS,ARG_SAV,WZ
      DOUBLE PRECISION SIG,LT,ARG_RE,ARG_IM,WZ_RE,WZ_IM
      PARAMETER (DM = 0.51, TAU = 1.51)


C.....DO THE CALCULATION:

      PRINT*
      PRINT*, 'SIG    LT       ARGS                             WZ'

      DO SL=10,1,-1         
         SIG = (0.1*SL)
         PRINT* 

         DO LL=0,20,1            
            LT = -1 + (0.5*LL)

            ARG_RE = (DM*SIG)/(SQRT(2.0))
            ARG_IM = ((LT*TAU)-(SIG*SIG))/(SIG*TAU*SQRT(2.0))
            
            ARGS = CMPLX(ARG_RE,ARG_IM)

            ARG_SAV=ARGS
            
            WZ = CWERF(ARGS)

            WZ_RE=DREAL(WZ)
            WZ_IM=DIMAG(WZ)
                       
            PRINT 5,SIG,LT,ARG_SAV,WZ_RE,WZ_IM     
 5          FORMAT (1X,F4.2,2X,F4.1,3X,F10.6,' + ',F10.6,' i',
     +           4X,F10.6,' + ',F10.6,' i')
            
         END DO
      END DO

      END

C----------------------------------------------------------
c.....CWERF FUNCTION DIRECTLY FROM THE CERNLIB SOURCES.....
C----------------------------------------------------------

      FUNCTION CWERF(Z)

      COMPLEX*16 CWERF,Z,ZH,R(37),S,T,V,W

      PARAMETER (Z1 = 1, HF = Z1/2, Z10 = 10)
      PARAMETER (C1 = 74/Z10, C2 = 83/Z10, C3 = Z10/32, C4 = 16/Z10)
      PARAMETER (C = 1.12837916709551257D0, P = (2*C4)**33)

      DOUBLE PRECISION GREAL,GIMAG,XARG,YARG
      COMPLEX*16 ZARG,GCONJG,GCMPLX

      GREAL(ZARG)=DREAL(ZARG)
      GIMAG(ZARG)=DIMAG(ZARG)
      GCONJG(ZARG)=CONJG(ZARG)
      GCMPLX(XARG,YARG)=CMPLX(XARG,YARG)

c     can't figure out what type X is supposed to be !?
      X=Z
      Y=GIMAG(Z)
      XA=ABS(X)
      YA=ABS(Y)
      IF(YA .LT. C1 .AND. XA .LT. C2) THEN
         ZH=GCMPLX(YA+C4,XA)
         R(37)=0
         DO N = 36,1,-1
            T=ZH+N*GCONJG(R(N+1))
            R(N)=HF*T/(GREAL(T)**2+GIMAG(T)**2)
         END DO
         XL=P
         S=0
         DO N = 33,1,-1
            XL=C3*XL
            S=R(N)*(S+XL)
         END DO
         V=C*S
      ELSE
         ZH=GCMPLX(YA,XA)
         R(1)=0
         DO N = 9,1,-1
            T=ZH+N*GCONJG(R(1))
            R(1)=HF*T/(GREAL(T)**2+GIMAG(T)**2)
         END DO
         V=C*R(1)
      END IF
      IF(YA .EQ. 0) V=GCMPLX(EXP(-XA**2),GIMAG(V))
      IF(Y .LT. 0) THEN
         V=2*EXP(-GCMPLX(XA,YA)**2)-V
      IF(X .GT. 0) V=GCONJG(V)
      ELSE
      IF(X .LT. 0) V=GCONJG(V)
      END IF

      CWERF=V

      RETURN
      END
