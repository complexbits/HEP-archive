C---------------------------------------------------
C     A PROGRAM TO MIMICK MATHEMATICA'S ERFI[Z]
C---------------------------------------------------

      PROGRAM JAMIESCOMPLEX

      IMPLICIT NONE
      
C     DECLARE OUR COMPLEX ARGUMENTS:

      COMPLEX*16 Z,ARG_SAV,CE,ERFI
      REAL*8 SIG,LT,ARG_RE,ARG_IM,CE_RE,CE_IM
      REAL*8 DM,TAU,SMAX,SMIN,TMAX,TMIN

      PARAMETER (DM = 0.51, TAU = 1.51)

c      PARAMETER (SMAX=1.,SMIN=1.)
c      PARAMETER (TMAX=5.0,TMIN=5.0)

      PARAMETER (SMAX=1.,SMIN=0)
      PARAMETER (TMAX=10.0,TMIN=-2.0)


C     DO THE CALCULATION:

      PRINT*
      PRINT*, 'SIG    LT       ARGS                             WZ'

      DO SIG=SMAX,SMIN,-0.1         

         PRINT* 

         DO LT=TMIN,TMAX,0.5           

            ARG_RE = (DM*SIG)/(SQRT(2.0))
            ARG_IM = ((LT*TAU)-(SIG*SIG))/(SIG*TAU*SQRT(2.0))
            
            Z = CMPLX(ARG_RE,ARG_IM)

C            leave these here for bugfinding
C            PRINT*, ARG_RE, ARG_IM
C            PRINT*, REAL(Z),AIMAG(Z)

            ARG_SAV=Z
            
            CE = ERFI(Z)

            CE_RE=DREAL(CE)
            CE_IM=DIMAG(CE)
                       
            PRINT 5,SIG,LT,ARG_SAV,CE_RE,CE_IM   
 5          FORMAT (1X,F4.2,1X,F4.1,2X,E11.4,', ',E11.4,' i',
     +           3X,E11.4,', ',E11.4,' i')
            
         END DO
      END DO

      END

C------------------------------------------------------

      FUNCTION ERFI(Z)

      IMPLICIT NONE

      COMPLEX*16 ERFI,Z,CE_K1,CE_K
      REAL*8 A,CE_K2
      INTEGER*8 K,K_FACT,KMAX,B

C     THIS IS 2/SQRT(PI)
      PARAMETER (A=1.12837916709551257D0)


      
C      PRINT*, REAL(Z),AIMAG(Z),KMAX

C      KMAX=ABS(REAL(10*Z*Z))
C      can't figure out how to do numbers larger than "15!" 
      KMAX=100000
      
      K_FACT=1

      CE_K = Z
      ERFI = A*CE_K

      CE_K1 = Z
      CE_K2 = 1

      DO K=1,KMAX,1

         CE_K1 = CE_K1*Z*Z/(2*K + 1)
   
         CE_K2 = CE_K2/K
            
         CE_K = CE_K1*CE_K2
         
         ERFI = ERFI + A*CE_K

C         PRINT*, CE_K1,CE_K2,ERFI
         
      END DO

C      PRINT*, ERFI,CE_K,K_FACT,ABS(DREAL(10*Z*Z))

      RETURN
      END
