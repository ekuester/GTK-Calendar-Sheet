!
!     Programmliste *kalenda*
!     Das Programm berechnet fuer beliebige, einzugebende Jahreszahlen
!     zwischen 1700 und 2099 den zugehoerigen Kalender.
!
!     nach Bild der Wissenschaft
!     E. Kuester, Mai 1974, November 1976, Mai 1987
!     letzte Aenderung fuer gfortran 20. Dezember 2013
      program kalend
      integer a,b,c,d,e,f,febr,i,j,jahr,k,mon,s,schalt,t,wotag
      integer monat(12,42),monate(5,12),tage(12,2)
      real stelle(4,18)
      common monat,monate,stelle,tage,wotag
      data monate/2hJA,2hNU,2hAR,2h  ,2h  ,2hFE,2hBR,2hUA,2hR ,2h  ,2hMA,2&
      hER,2hZ ,2h  ,2h  ,2hAP,2hRI,2hL ,2h  ,2h  ,2hMA,2hI ,2h  ,2h  ,2h  ,&
      2hJU,2hNI,2h  ,2h  ,2h  ,2hJU,2hLI,2h  ,2h  ,2h  ,2hAU,2hGU,2hS&
      T,2h  ,2h  ,2hSE,2hPT,2hEM,2hBE,2hR ,2hOK,2hTO,2hBE,2hR ,2h  ,2hNO&
      ,2hVE,2hMB,2hER,2h  ,2hDE,2hZE,2hMB,2hER,2h  /
      data tage/31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31/
      write(*,1000)
 1000 format(15h Welches Jahr? )
      read(*,2000) jahr
 2000 format(i4)
      write(*,3000) jahr
 3000 format(1x,13hKalender für ,1x,i4)
      a=jahr/100
      b=mod(jahr,1000)
      c=mod(jahr,100)
      d=mod(jahr,4)
      schalt=1
      if (d.eq.0) schalt=2
      e=mod(a,4)
      if (c.eq.0.and.e.ne.0) schalt=1
      f=a
      if (a.gt.19) f=19
      i=2*(19-f)
      f=jahr-100*f
      j=jahr
      k=4
   10 s=mod(j,10)
      call jana(k,s)
      j=j/10
      k=k-1
      if(k.ne.0) goto 10
      wotag=f+f/4+i
      if (schalt.eq.1) wotag=wotag+1
      do 200 mon=1,12
      wotag=mod(wotag,7)
      t=tage(mon,schalt)
      if (mon.eq.2) febr=t
      call mona(mon,t)
  200 wotag=wotag+t
      call rita()
      call frieda(jahr,febr)
      end

!     Jahreszahl in Feld einlesen
      subroutine jana(n,s)
      integer j,k,l,n,s,wotag
      integer monat(12,42),monate(5,12),tage(12,2)
      real stelle(4,18),z(180)
      common monat,monate,stelle,tage,wotag
      data z/4h 000,4h000 ,4h00  ,4h  00,4h00  ,4h  00,4h00  ,4h  00,4h00  ,&
      4h  00,4h00  ,4h  00,4h00  ,4h  00,4h00  ,4h  00,4h 000,4h000 ,4h   1,&
      4h1   ,4h  1l,4h1   ,4h   1,4h1   ,4h   1,4h1   ,4h   1,4h1   ,4h   1,&
      4h1   ,4h   1,4h1   ,4h   1,4hl   ,4h11ll,4h1111,4h 222,4h222 ,4h22  ,&
      4h  22,4h    ,4h  22,4h   2,4h222 ,4h  22,4h    ,4h 22 ,4h    ,4h22  ,&
      4h    ,4h22  ,4h    ,4h2222,4h2222,4h 333,4h333 ,4h33  ,4h  33,4h    ,&
      4h  33,4h   3,4h 333,4h    ,4h  33,4h    ,4h  33,4h    ,4h  33,4h33  ,&
      4h  33,4h 333,4h333 ,4h    ,4h 44 ,4h    ,4h444 ,4h   4,4h444 ,4h  44,&
      4h 44 ,4h 44 ,4h 44 ,4h4444,4h4444,4h    ,4h 44 ,4h    ,4h 44 ,4h    ,&
      4h 44 ,4h 555,4h5555,4h55  ,4h    ,4h55  ,4h    ,4h5555,4h555 ,4h    ,&
      4h  55,4h    ,4h  55,4h    ,4h  55,4h55  ,4h  55,4h 55S,4h555 ,4h 666,&
      4h666 ,4h66  ,4h  66,4h66  ,4h    ,4h6666,4h666 ,4h66  ,4h  66,4h66  ,&
      4h  66,4h66  ,4h  66,4h66  ,4h  66,4h 666,4h666 ,4h7777,4h7777,4h    ,&
      4h 77 ,4h    ,4h77  ,4h   7,4h7   ,4h   7,4h7   ,4h   7,4h7   ,4h   7,&
      4h7   ,4h   7,4h7   ,4h   7,4h7   ,4h 888,4h888 ,4h88  ,4h  88,4h88  ,&
      4h  88,4h 888,4h888 ,4h88  ,4h  88,4h88  ,4h  8B,4h88  ,4h  88,4h88  ,&
      4h  88,4h 888,4h888 ,4h 999,4h999 ,4h99  ,4h  99,4h99  ,4h  99,4h99  ,&
      4h  99,4h99  ,4h  99,4h 999,4h999 ,4h    ,4h  99,4h99  ,4h  99,4h 999,&
      4h999 /
      k=18*s
      do 100 l=1,18
      j=k+l
  100 stelle(n,l)=z(j)
      return
      end

!     Fuellen der Monatsfelder
      subroutine mona(mon,ta)
      integer i,j,moma(31),monat(12,42),monate(5,12),n,nichts,ta,tage(12,2),wotag
      real stelle(4,18)
      common monat,monate,stelle,tage,wotag
      data moma/2h 1,2h 2,2h 3,2h 4,2h 5,2h 6,2h 7,2h 8,2h 9,2h10,2h11,&
      2h12,2h13,2h14,2h15,2h16,2h17,2h18,2h19,2h20,2h21,2h22,2h23,2h24,&
      2h25,2h26,2h27,2h28,2h29,2h30,2h31/
      data nichts/2h  /
      do 100 i=1,42
  100 monat(mon,i)=nichts
      j=wotag-1
      if (j.lt.0) j=6
      do 200 i=1,ta
      n=i+j
  200 monat(mon,n)=moma(i)
      return
      end

!     Ausdruck des Kalenders
      subroutine rita()
      integer a,e,i,index,j,k,l,m,wotag
      integer monat(12,42),monate(5,12),tage(12,2)
      real stelle(4,18)
      common monat,monate,stelle,tage,wotag
      do 100 i=1,18,2
      write(*,1000) (stelle(j,i),stelle(j,i+1),j=1,4)
 1000 format(23x,4(2a4,2x))
  100 continue
      do 300 i=1,4
      m=3*i
      l=m-2
      write(*,2000) ((monate(j,k),j=1,5),k=l,m)
 2000 format(5x,3(5a2,13x))
      write(*,3000)
 3000 format(5x,3(2hMO,1x,2hDI,1x,2hMI,1x,2hDO,1x,2hFR,1x,2hSA,1x,2hSO,3x))
      do 200 index=1,6
      e=7*index
      a=e-6
  200 write(*,4000) ((monat(k,j),j=a,e),k=l,m)
 4000 format(5x,7(a2,1x),2x,7(a2,1x),2x,7(a2,1x))
  300 continue
      return
      end

!     Berechnung und Ausgabe der Feiertage
      subroutine frieda(jahr,febr)
      integer a,b,c,d,e,i,jahr,m,n,febr,wotag
      integer monat(12,42),monate(5,12),tage(12,2)
      integer bbt,fron,himm,karf,ost,pfin,ros,ts,vtt
      integer fmon,hmon,kmon,omon,pmon,rmon
      real stelle(4,18)
      common monat,monate,stelle,tage,wotag
!     Ostern nach der Gauss'schen Formel
      m=24
      n=6
      if (jahr.lt.2100) n=5
      if (jahr.gt.1899) goto 10
      m=23
      n=4
      if (jahr.lt.l800) n=3
      if (jahr.lt.1700) n=2
   10 a=mod(jahr,19)
      b=mod(jahr,4)
      c=mod(jahr,7)
      d=mod(19*a+m,30)
      e=mod(b+b+4*c+6*d+n,7)
!     Ostersonntag als Datum im Maerz
      ost=22+d+e
      omon=3
!     Rosenmontag als Datum im Maerz (auch negativ)
      ros=ost-48
      rmon=3
      if (ros.gt.0) goto 20
      ros=ros+febr
      rmon=2
   20 if (ost.le.31) goto 30
!     Ostern ist im April
      ost=ost-31
      omon=4
      if (ost.eq.26.or.(ost.eq.25.and.d.eq.28.and.a.gt.19)) ost=19
   30 kmon=omon
      karf=ost-2
      if (karf.gt.6) goto 40
      kmon=kmon-1
      karf=karf+31
   40 hmon=omon+1
      himm=ost+39-30
      if (himm.lt.32) goto 50
      hmon=hmon+1
      himm=himm-31
   50 pmon=hmon
      pfin=himm+10
      if (pfin.lt.32) goto 60
      pmon=pmon+1
      pfin=pfin-31
   60 fmon=pmon
      fron=pfin+11
      if (fron.lt.32) goto 70
      fmon=fmon+1
      fron=fron-31
!     Feiertage im November
!     Wochentag zurueckrechnen von Dezember
  70 wotag=mod(wotag-26,7)
      vtt=8-wotag
      if (wotag.lt.3) vtt=vtt-7
      vtt=vtt+14
      bbt=vtt+3
      ts=vtt+7
      write(*,1000) (monate(i,1),i=1,5)
 1000 format(5x,7hNEUJAHR,16x,3h 1.,5a2)
      write(*,2000) ros,(monate(i,rmon),i=1,5)
 2000 format(5x,11hROSENMONTAG,12x,i2,1h.,5a2)
      write(*,3000) karf,(monate(i,kmon),i=1,5)
 3000 format(5x,10hKARFREITAG,13x,i2,1h.,5a2)
      write(*,4000) ost,(monate(i,omon),i=1,5)
 4000 format(5x,6hOSTERN,17x,i2,1h.,5a2)
      write(*,4500) (monate(i,5),i=1,5)
 4500 format(5x,14hTAG DER ARBEIT,9x,3h 1.,5a2)
      write(*,5000) himm,(monate(i,hmon),i=1,5)
 5000 format(5x,19hCHRISTI HIMMELFAHRT,4x,i2,1h.,5a2)
      write(*,6000) pfin,(monate(i,pmon),i=1,5)
 6000 format(5x,9hPFINGSTEN,14x,i2,1h.,5a2)
      if (fron.gt.17.and.fmon.eq.6) goto 80
      write(*,7000) fron,(monate(i,fmon),i=1,5)
 7000 format(5x,12hFRONLEICHNAM,11x,i2,1h.,5a2)
   80 write(*,8000) (monate(i,6),i=1,5)
 8000 format(5x,15hTAG DER EINHEIT,8x,3h17.,5a2)
      if (fron.gt.17.and.fmon.eq.6) write(*,7000) fron,(monate(i,fmon),i=1,5)
      write(*,8500) (monate(i,11),i=1,5)
 8500 format(5x,13hALLERHEILIGEN,10x,3h 1.,5a2)
      write(*,9000) bbt,(monate(i,11),i=1,5)
 9000 format(5x,16hBUSS- UND BETTAG,7x,i2,1h.,5a2)
      write(*,9100) (monate(i,12),i=1,5)
 9100 format(5x,11hHEILIGABEND,12x,3h24.,5a2)
      write(*,9200)
 9200 format(40x,16hA happy new year)
      write(*,9300)
 9300 format(40x,26hLet's hope it's a good one)
      write(*,9400)
 9400 format(40x,20hWithout any fear ...)
      return
      end
