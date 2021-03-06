#ifndef BGC_STRUCT_H
#define BGC_STRUCT_H

/* simulation control variables */
typedef struct
{
    //    int             metyears;   /* # years of met data */
    //    int             simyears;   /* # years of simulation */
    double          simstarttime;   /* start time of simulation */
    double          simendtime; /* end time of simulation */
    int             spinup;     /* (flag) 1=spinup run, 0=normal run */
    int             maxspinyears;   /* maximum number of years for spinup run */
    int             dodaily;    /* flag for daily output */
    int             domonavg;   /* flag for monthly average of daily outputs */
    int             doannavg;   /* flag for annual average of daily outputs */
    int             doannual;   /* flag for annual output */
    int             ndayout;    /* number of daily outputs */
    int             nannout;    /* number of annual outputs */
    int            *daycodes;   /* array of indices for daily outputs */
    int            *anncodes;   /* array of indices for annual outputs */
    int             read_restart;   /* flag to read restart file */
    int             write_restart;  /* flag to write restart file */
    int             keep_metyr; /* (flag) 1=retain restart metyr, 0=reset metyr */
    int             onscreen;   /* (flag) 1=show progress on-screen 0=don't */
    int             spinupstart;    /* first met year for spinup */
    int             spinupend;  /* last met year for spinup */
} control_struct;


/* a structure to hold information on the annual co2 concentration */
typedef struct
{
    int             varco2;     /* (flag) 0=const 1=use file 2=const,file for Ndep */
    double          co2ppm;     /* (ppm)  constant CO2 concentration */
    double         *co2ppm_array;   /* (ppm)  annual CO2 concentration array */
    int            *co2year_array;  /* (year) year corresponding to the concentration value in co2ppm_arry */
    int             co2vals;    /* (num)  The number of CO2 concentration values in the co2ppm_array */
} co2control_struct;

/* a structure to hold annual nitrogen deposition data */
typedef struct
{
    int             varndep;    /* (flag) 0=const 1=use file  */
    //double          ndep;       /* (kgN m-2 yr-1)  constant ndep value */
    double         *ndep_array; /* (kgN m-2 yr-1)  annual ndep array */
    int            *ndepyear_array; /* (year) year corresponding to the ndep value in ndep_array */
    int             ndepvals;   /* (num)  The number of ndep values in the ndep_array */
    double          ndep;       /* (kgN/m2/yr) wet+dry atmospheric deposition of N */
    double          nfix;       /* (kgN/m2/yr) symbiotic+asymbiotic fixation of N */
} ndepcontrol_struct;

/* meteorological variable arrays */
/* inputs from mtclim, except for tavg and tavg_ra
 * which are used for an 11-day running average of daily average air T,
 * computed for the whole length of the met array prior to the 
 * daily model loop */
typedef struct
{
    double         *tmax;       /* (deg C) daily maximum air temperature */
    double         *tmin;       /* (deg C) daily minimum air temperature */
    double         *prcp;       /* (cm)    precipitation */
    double         *vpd;        /* (Pa)    vapor pressure deficit */
    double         *swavgfd;    /* (W/m2)  daylight avg shortwave flux density */
    double         *par;        /* (W/m2)  photosynthetically active radiation */
    double         *dayl;       /* (s)     daylength */
    double         *prev_dayl;
    double         *tavg;       /* (deg C) daily average temperature */
    double         *tday;
    double         *tnight;
    double         *tsoil;
    double         *swc;
    double         *pa;
    double         *tavg_ra;    /* (deg C) 11-day running avg of daily avg temp */
} metarr_struct;

/* daily values that are passed to daily model subroutines */
typedef struct
{
    double          prcp;       /* (kg/m2) precipitation */
    double          tmax;       /* (deg C) daily maximum air temperature */
    double          tmin;       /* (deg C) daily minimum air temperature */
    double          tavg;       /* (deg C) daily average air temperature */
    double          tday;       /* (deg C) daylight average air temperature */
    double          tnight;     /* (deg C) nightime average air temperature */
    double          tsoil;      /* (deg C) daily soil temperature, avg, top 10 cm */
    double          swc;
    double          vpd;        /* (Pa)    vapor pressure deficit */
    double          swavgfd;    /* (W/m2)  daylight average shortwave flux */
    double          swabs;      /* (W/m2)  canopy absorbed shortwave flux */
    double          swtrans;    /* (W/m2)  transmitted shortwave flux */
    double          swabs_per_plaisun;  /* (W/m2) swabs per unit sunlit proj LAI */
    double          swabs_per_plaishade;    /* (W/m2) swabs per unit shaded proj LAI */
    double          ppfd_per_plaisun;   /* (umol/m2/s) ppfd per unit sunlit proj LAI */
    double          ppfd_per_plaishade; /* (umol/m2/s) ppfd per unit shaded proj LAI */
    double          par;        /* (W/m2)  photosynthetically active radiation */
    double          parabs;     /* (W/m2)  PAR absorbed by canopy */
    double          pa;         /* (Pa)    atmospheric pressure */
    double          co2;        /* (ppm)   atmospheric concentration of CO2 */
    double          dayl;       /* (s)     daylength */
    double          prev_dayl;  /* daylength from previous timestep (seconds) */
} metvar_struct;

/* water state variables (including sums for sources and sinks) */
typedef struct
{
    double          soilw;      /* (kgH2O/m2) water stored in soil */
    double          snoww;      /* (kgH2O/m2) water stored in snowpack */
    double          canopyw;    /* (kgH2O/m2) water stored on canopy */
    double          prcp_src;   /* (kgH2O/m2) SUM of precipitation */
    double          outflow_snk;    /* (kgH2O/m2) SUM of outflow */
    double          soilevap_snk;   /* (kgH2O/m2) SUM of soil water evaporation */
    double          snowsubl_snk;   /* (kgH2O/m2) SUM of snow water sublimation */
    double          canopyevap_snk; /* (kgH2O/m2) SUM of canopy water evaporation */
    double          trans_snk;  /* (kgH2O/m2) SUM of transpiration */
} wstate_struct;

/* water flux variables */
typedef struct
{
    double          prcp_to_canopyw;    /* (kgH2O/m2/d) interception on canopy */
    double          prcp_to_soilw;  /* (kgH2O/m2/d) precip entering soilwater pool */
    double          prcp_to_snoww;  /* (kgH2O/m2/d) snowpack accumulation */
    double          canopyw_evap;   /* (kgH2O/m2/d) evaporation from canopy */
    double          canopyw_to_soilw;   /* (kgH2O/m2/d) canopy drip and stemflow */
    double          snoww_subl; /* (kgH2O/m2/d) sublimation from snowpack */
    double          snoww_to_soilw; /* (kgH2O/m2/d) melt from snowpack */
    double          soilw_evap; /* (kgH2O/m2/d) evaporation from soil */
    double          soilw_trans;    /* (kgH2O/m2/d) transpiration */
    double          soilw_outflow;  /* (kgH2O/m2/d) outflow */
    double          et;         /* (kgH20/m2/d) evapotranspiration */
} wflux_struct;

/* carbon state initialization structure */
typedef struct
{
    double          max_leafc;  /* (kgC/m2) first-year displayed + stored leafc */
    double          max_stemc;  /* (kgC/m2) first-year total stem carbon */
} cinit_struct;

/* carbon state variables (including sums for sources and sinks) */
typedef struct
{
    double          leafc;      /* (kgC/m2) leaf C */
    double          leafc_storage;  /* (kgC/m2) leaf C storage */
    double          leafc_transfer; /* (kgC/m2) leaf C transfer */
    double          frootc;     /* (kgC/m2) fine root C */
    double          frootc_storage; /* (kgC/m2) fine root C storage */
    double          frootc_transfer;    /* (kgC/m2) fine root C transfer */
    double          livestemc;  /* (kgC/m2) live stem C */
    double          livestemc_storage;  /* (kgC/m2) live stem C storage */
    double          livestemc_transfer; /* (kgC/m2) live stem C transfer */
    double          deadstemc;  /* (kgC/m2) dead stem C */
    double          deadstemc_storage;  /* (kgC/m2) dead stem C storage */
    double          deadstemc_transfer; /* (kgC/m2) dead stem C transfer */
    double          livecrootc; /* (kgC/m2) live coarse root C */
    double          livecrootc_storage; /* (kgC/m2) live coarse root C storage */
    double          livecrootc_transfer;    /* (kgC/m2) live coarse root C transfer */
    double          deadcrootc; /* (kgC/m2) dead coarse root C */
    double          deadcrootc_storage; /* (kgC/m2) dead coarse root C storage */
    double          deadcrootc_transfer;    /* (kgC/m2) dead coarse root C transfer */
    double          gresp_storage;  /* (kgC/m2) growth respiration storage */
    double          gresp_transfer; /* (kgC/m2) growth respiration transfer */
    double          cwdc;       /* (kgC/m2) coarse woody debris C */
    double          litr1c;     /* (kgC/m2) litter labile C */
    double          litr2c;     /* (kgC/m2) litter unshielded cellulose C */
    double          litr3c;     /* (kgC/m2) litter shielded cellulose C */
    double          litr4c;     /* (kgC/m2) litter lignin C */
    double          soil1c;     /* (kgC/m2) microbial recycling pool C (fast) */
    double          soil2c;     /* (kgC/m2) microbial recycling pool C (medium) */
    double          soil3c;     /* (kgC/m2) microbial recycling pool C (slow) */
    double          soil4c;     /* (kgC/m2) recalcitrant SOM C (humus, slowest) */
    double          cpool;      /* (kgC/m2) temporary photosynthate C pool */
    double          psnsun_src; /* (kgC/m2) SUM of gross PSN from sulit canopy */
    double          psnshade_src;   /* (kgC/m2) SUM of gross PSN from shaded canopy */
    double          leaf_mr_snk;    /* (kgC/m2) SUM of leaf maint resp */
    double          leaf_gr_snk;    /* (kgC/m2) SUM of leaf growth resp */
    double          froot_mr_snk;   /* (kgC/m2) SUM of fine root maint resp */
    double          froot_gr_snk;   /* (kgC/m2) SUM of fine root growth resp */
    double          livestem_mr_snk;    /* (kgC/m2) SUM of live stem maint resp */
    double          livestem_gr_snk;    /* (kgC/m2) SUM of live stem growth resp */
    double          deadstem_gr_snk;    /* (kgC/m2) SUM of dead stem growth resp */
    double          livecroot_mr_snk;   /* (kgC/m2) SUM of live coarse root maint resp */
    double          livecroot_gr_snk;   /* (kgC/m2) SUM of live coarse root growth resp */
    double          deadcroot_gr_snk;   /* (kgC/m2) SUM of dead coarse root growth resp */
    double          litr1_hr_snk;   /* (kgC/m2) SUM of labile litr microbial resp */
    double          litr2_hr_snk;   /* (kgC/m2) SUM of cellulose litr microbial resp */
    double          litr4_hr_snk;   /* (kgC/m2) SUM of lignin litr microbial resp */
    double          soil1_hr_snk;   /* (kgC/m2) SUM of fast microbial respiration */
    double          soil2_hr_snk;   /* (kgC/m2) SUM of medium microbial respiration */
    double          soil3_hr_snk;   /* (kgC/m2) SUM of slow microbial respiration */
    double          soil4_hr_snk;   /* (kgC/m2) SUM of recalcitrant SOM respiration */
    double          fire_snk;   /* (kgC/m2) SUM of fire losses */
} cstate_struct;

/* daily carbon flux variables */
typedef struct
{
    /* mortality fluxes */
    double          m_leafc_to_litr1c;  /* (kgC/m2/d) */
    double          m_leafc_to_litr2c;  /* (kgC/m2/d) */
    double          m_leafc_to_litr3c;  /* (kgC/m2/d) */
    double          m_leafc_to_litr4c;  /* (kgC/m2/d) */
    double          m_frootc_to_litr1c; /* (kgC/m2/d) */
    double          m_frootc_to_litr2c; /* (kgC/m2/d) */
    double          m_frootc_to_litr3c; /* (kgC/m2/d) */
    double          m_frootc_to_litr4c; /* (kgC/m2/d) */
    double          m_leafc_storage_to_litr1c;  /* (kgC/m2/d) */
    double          m_frootc_storage_to_litr1c; /* (kgC/m2/d) */
    double          m_livestemc_storage_to_litr1c;  /* (kgC/m2/d) */
    double          m_deadstemc_storage_to_litr1c;  /* (kgC/m2/d) */
    double          m_livecrootc_storage_to_litr1c; /* (kgC/m2/d) */
    double          m_deadcrootc_storage_to_litr1c; /* (kgC/m2/d) */
    double          m_leafc_transfer_to_litr1c; /* (kgC/m2/d) */
    double          m_frootc_transfer_to_litr1c;    /* (kgC/m2/d) */
    double          m_livestemc_transfer_to_litr1c; /* (kgC/m2/d) */
    double          m_deadstemc_transfer_to_litr1c; /* (kgC/m2/d) */
    double          m_livecrootc_transfer_to_litr1c;    /* (kgC/m2/d) */
    double          m_deadcrootc_transfer_to_litr1c;    /* (kgC/m2/d) */
    double          m_livestemc_to_cwdc;    /* (kgC/m2/d) */
    double          m_deadstemc_to_cwdc;    /* (kgC/m2/d) */
    double          m_livecrootc_to_cwdc;   /* (kgC/m2/d) */
    double          m_deadcrootc_to_cwdc;   /* (kgC/m2/d) */
    double          m_gresp_storage_to_litr1c;  /* (kgC/m2/d) */
    double          m_gresp_transfer_to_litr1c; /* (kgC/m2/d) */
    /* fire fluxes */
    double          m_leafc_to_fire;    /* (kgC/m2/d) */
    double          m_frootc_to_fire;   /* (kgC/m2/d) */
    double          m_leafc_storage_to_fire;    /* (kgC/m2/d) */
    double          m_frootc_storage_to_fire;   /* (kgC/m2/d) */
    double          m_livestemc_storage_to_fire;    /* (kgC/m2/d) */
    double          m_deadstemc_storage_to_fire;    /* (kgC/m2/d) */
    double          m_livecrootc_storage_to_fire;   /* (kgC/m2/d) */
    double          m_deadcrootc_storage_to_fire;   /* (kgC/m2/d) */
    double          m_leafc_transfer_to_fire;   /* (kgC/m2/d) */
    double          m_frootc_transfer_to_fire;  /* (kgC/m2/d) */
    double          m_livestemc_transfer_to_fire;   /* (kgC/m2/d) */
    double          m_deadstemc_transfer_to_fire;   /* (kgC/m2/d) */
    double          m_livecrootc_transfer_to_fire;  /* (kgC/m2/d) */
    double          m_deadcrootc_transfer_to_fire;  /* (kgC/m2/d) */
    double          m_livestemc_to_fire;    /* (kgC/m2/d) */
    double          m_deadstemc_to_fire;    /* (kgC/m2/d) */
    double          m_livecrootc_to_fire;   /* (kgC/m2/d) */
    double          m_deadcrootc_to_fire;   /* (kgC/m2/d) */
    double          m_gresp_storage_to_fire;    /* (kgC/m2/d) */
    double          m_gresp_transfer_to_fire;   /* (kgC/m2/d) */
    double          m_litr1c_to_fire;   /* (kgC/m2/d) */
    double          m_litr2c_to_fire;   /* (kgC/m2/d) */
    double          m_litr3c_to_fire;   /* (kgC/m2/d) */
    double          m_litr4c_to_fire;   /* (kgC/m2/d) */
    double          m_cwdc_to_fire; /* (kgC/m2/d) */
    /* phenology fluxes from transfer pool */
    double          leafc_transfer_to_leafc;    /* (kgC/m2/d) */
    double          frootc_transfer_to_frootc;  /* (kgC/m2/d) */
    double          livestemc_transfer_to_livestemc;    /* (kgC/m2/d) */
    double          deadstemc_transfer_to_deadstemc;    /* (kgC/m2/d) */
    double          livecrootc_transfer_to_livecrootc;  /* (kgC/m2/d) */
    double          deadcrootc_transfer_to_deadcrootc;  /* (kgC/m2/d) */
    /* leaf and fine root litterfall */
    double          leafc_to_litr1c;    /* (kgC/m2/d) */
    double          leafc_to_litr2c;    /* (kgC/m2/d) */
    double          leafc_to_litr3c;    /* (kgC/m2/d) */
    double          leafc_to_litr4c;    /* (kgC/m2/d) */
    double          frootc_to_litr1c;   /* (kgC/m2/d) */
    double          frootc_to_litr2c;   /* (kgC/m2/d) */
    double          frootc_to_litr3c;   /* (kgC/m2/d) */
    double          frootc_to_litr4c;   /* (kgC/m2/d) */
    /* maintenance respiration fluxes */
    double          leaf_day_mr;    /* (kgC/m2/d) */
    double          leaf_night_mr;  /* (kgC/m2/d) */
    double          froot_mr;   /* (kgC/m2/d) */
    double          livestem_mr;    /* (kgC/m2/d) */
    double          livecroot_mr;   /* (kgC/m2/d) */
    /* photosynthesis flux */
    double          psnsun_to_cpool;    /* (kgC/m2/d) */
    double          psnshade_to_cpool;  /* (kgC/m2/d) */
    /* litter decomposition fluxes */
    double          cwdc_to_litr2c; /* (kgC/m2/d) */
    double          cwdc_to_litr3c; /* (kgC/m2/d) */
    double          cwdc_to_litr4c; /* (kgC/m2/d) */
    double          litr1_hr;   /* (kgC/m2/d) */
    double          litr1c_to_soil1c;   /* (kgC/m2/d) */
    double          litr2_hr;   /* (kgC/m2/d) */
    double          litr2c_to_soil2c;   /* (kgC/m2/d) */
    double          litr3c_to_litr2c;   /* (kgC/m2/d) */
    double          litr4_hr;   /* (kgC/m2/d) */
    double          litr4c_to_soil3c;   /* (kgC/m2/d) */
    double          soil1_hr;   /* (kgC/m2/d) */
    double          soil1c_to_soil2c;   /* (kgC/m2/d) */
    double          soil2_hr;   /* (kgC/m2/d) */
    double          soil2c_to_soil3c;   /* (kgC/m2/d) */
    double          soil3_hr;   /* (kgC/m2/d) */
    double          soil3c_to_soil4c;   /* (kgC/m2/d) */
    double          soil4_hr;   /* (kgC/m2/d) */
    /* daily allocation fluxes from current GPP */
    double          cpool_to_leafc; /* (kgC/m2/d) */
    double          cpool_to_leafc_storage; /* (kgC/m2/d) */
    double          cpool_to_frootc;    /* (kgC/m2/d) */
    double          cpool_to_frootc_storage;    /* (kgC/m2/d) */
    double          cpool_to_livestemc; /* (kgC/m2/d) */
    double          cpool_to_livestemc_storage; /* (kgC/m2/d) */
    double          cpool_to_deadstemc; /* (kgC/m2/d) */
    double          cpool_to_deadstemc_storage; /* (kgC/m2/d) */
    double          cpool_to_livecrootc;    /* (kgC/m2/d) */
    double          cpool_to_livecrootc_storage;    /* (kgC/m2/d) */
    double          cpool_to_deadcrootc;    /* (kgC/m2/d) */
    double          cpool_to_deadcrootc_storage;    /* (kgC/m2/d) */
    double          cpool_to_gresp_storage; /* (kgC/m2/d) */
    /* daily growth respiration fluxes */
    double          cpool_leaf_gr;  /* (kgC/m2/d) */
    double          cpool_leaf_storage_gr;  /* (kgC/m2/d) */
    double          transfer_leaf_gr;   /* (kgC/m2/d) */
    double          cpool_froot_gr; /* (kgC/m2/d) */
    double          cpool_froot_storage_gr; /* (kgC/m2/d) */
    double          transfer_froot_gr;  /* (kgC/m2/d) */
    double          cpool_livestem_gr;  /* (kgC/m2/d) */
    double          cpool_livestem_storage_gr;  /* (kgC/m2/d) */
    double          transfer_livestem_gr;   /* (kgC/m2/d) */
    double          cpool_deadstem_gr;  /* (kgC/m2/d) */
    double          cpool_deadstem_storage_gr;  /* (kgC/m2/d) */
    double          transfer_deadstem_gr;   /* (kgC/m2/d) */
    double          cpool_livecroot_gr; /* (kgC/m2/d) */
    double          cpool_livecroot_storage_gr; /* (kgC/m2/d) */
    double          transfer_livecroot_gr;  /* (kgC/m2/d) */
    double          cpool_deadcroot_gr; /* (kgC/m2/d) */
    double          cpool_deadcroot_storage_gr; /* (kgC/m2/d) */
    double          transfer_deadcroot_gr;  /* (kgC/m2/d) */
    /* annual turnover of storage to transfer pools */
    double          leafc_storage_to_leafc_transfer;    /* (kgC/m2/d) */
    double          frootc_storage_to_frootc_transfer;  /* (kgC/m2/d) */
    double          livestemc_storage_to_livestemc_transfer;    /* (kgC/m2/d) */
    double          deadstemc_storage_to_deadstemc_transfer;    /* (kgC/m2/d) */
    double          livecrootc_storage_to_livecrootc_transfer;  /* (kgC/m2/d) */
    double          deadcrootc_storage_to_deadcrootc_transfer;  /* (kgC/m2/d) */
    double          gresp_storage_to_gresp_transfer;    /* (kgC/m2/d) */
    /* turnover of live wood to dead wood */
    double          livestemc_to_deadstemc; /* (kgC/m2/d) */
    double          livecrootc_to_deadcrootc;   /* (kgC/m2/d) */
} cflux_struct;

/* nitrogen state variables (including sums for sources and sinks) */
typedef struct
{
    double          leafn;      /* (kgN/m2) leaf N */
    double          leafn_storage;  /* (kgN/m2) leaf N */
    double          leafn_transfer; /* (kgN/m2) leaf N */
    double          frootn;     /* (kgN/m2) fine root N */
    double          frootn_storage; /* (kgN/m2) fine root N */
    double          frootn_transfer;    /* (kgN/m2) fine root N */
    double          livestemn;  /* (kgN/m2) live stem N */
    double          livestemn_storage;  /* (kgN/m2) live stem N */
    double          livestemn_transfer; /* (kgN/m2) live stem N */
    double          deadstemn;  /* (kgN/m2) dead stem N */
    double          deadstemn_storage;  /* (kgN/m2) dead stem N */
    double          deadstemn_transfer; /* (kgN/m2) dead stem N */
    double          livecrootn; /* (kgN/m2) live coarse root N */
    double          livecrootn_storage; /* (kgN/m2) live coarse root N */
    double          livecrootn_transfer;    /* (kgN/m2) live coarse root N */
    double          deadcrootn; /* (kgN/m2) dead coarse root N */
    double          deadcrootn_storage; /* (kgN/m2) dead coarse root N */
    double          deadcrootn_transfer;    /* (kgN/m2) dead coarse root N */
    double          cwdn;       /* (kgN/m2) coarse woody debris N */
    double          litr1n;     /* (kgN/m2) litter labile N */
    double          litr2n;     /* (kgN/m2) litter unshielded cellulose N */
    double          litr3n;     /* (kgN/m2) litter shielded cellulose N */
    double          litr4n;     /* (kgN/m2) litter lignin N */
    double          soil1n;     /* (kgN/m2) microbial recycling pool N (fast) */
    double          soil2n;     /* (kgN/m2) microbial recycling pool N (medium) */
    double          soil3n;     /* (kgN/m2) microbial recycling pool N (slow) */
    double          soil4n;     /* (kgN/m2) recalcitrant SOM N (humus, slowest) */
    double          sminn;      /* (kgN/m2) soil mineral N */
    double          retransn;   /* (kgN/m2) plant pool of retranslocated N */
    double          npool;      /* (kgN/m2) temporary plant N pool */
    double          nfix_src;   /* (kgN/m2) SUM of biological N fixation */
    double          ndep_src;   /* (kgN/m2) SUM of N deposition inputs */
    double          nleached_snk;   /* (kgN/m2) SUM of N leached */
    double          nvol_snk;   /* (kgN/m2) SUM of N lost to volatilization */
    double          fire_snk;   /* (kgN/m2) SUM of N lost to fire */
} nstate_struct;

/* daily nitrogen flux variables */
typedef struct
{
    /* mortality fluxes */
    double          m_leafn_to_litr1n;  /* (kgN/m2/d) */
    double          m_leafn_to_litr2n;  /* (kgN/m2/d) */
    double          m_leafn_to_litr3n;  /* (kgN/m2/d) */
    double          m_leafn_to_litr4n;  /* (kgN/m2/d) */
    double          m_frootn_to_litr1n; /* (kgN/m2/d) */
    double          m_frootn_to_litr2n; /* (kgN/m2/d) */
    double          m_frootn_to_litr3n; /* (kgN/m2/d) */
    double          m_frootn_to_litr4n; /* (kgN/m2/d) */
    double          m_leafn_storage_to_litr1n;  /* (kgN/m2/d) */
    double          m_frootn_storage_to_litr1n; /* (kgN/m2/d) */
    double          m_livestemn_storage_to_litr1n;  /* (kgN/m2/d) */
    double          m_deadstemn_storage_to_litr1n;  /* (kgN/m2/d) */
    double          m_livecrootn_storage_to_litr1n; /* (kgN/m2/d) */
    double          m_deadcrootn_storage_to_litr1n; /* (kgN/m2/d) */
    double          m_leafn_transfer_to_litr1n; /* (kgN/m2/d) */
    double          m_frootn_transfer_to_litr1n;    /* (kgN/m2/d) */
    double          m_livestemn_transfer_to_litr1n; /* (kgN/m2/d) */
    double          m_deadstemn_transfer_to_litr1n; /* (kgN/m2/d) */
    double          m_livecrootn_transfer_to_litr1n;    /* (kgN/m2/d) */
    double          m_deadcrootn_transfer_to_litr1n;    /* (kgN/m2/d) */
    double          m_livestemn_to_litr1n;  /* (kgN/m2/d) */
    double          m_livestemn_to_cwdn;    /* (kgN/m2/d) */
    double          m_deadstemn_to_cwdn;    /* (kgN/m2/d) */
    double          m_livecrootn_to_litr1n; /* (kgN/m2/d) */
    double          m_livecrootn_to_cwdn;   /* (kgN/m2/d) */
    double          m_deadcrootn_to_cwdn;   /* (kgN/m2/d) */
    double          m_retransn_to_litr1n;   /* (kgN/m2/d) */
    /* fire fluxes */
    double          m_leafn_to_fire;    /* (kgN/m2/d) */
    double          m_frootn_to_fire;   /* (kgN/m2/d) */
    double          m_leafn_storage_to_fire;    /* (kgN/m2/d) */
    double          m_frootn_storage_to_fire;   /* (kgN/m2/d) */
    double          m_livestemn_storage_to_fire;    /* (kgN/m2/d) */
    double          m_deadstemn_storage_to_fire;    /* (kgN/m2/d) */
    double          m_livecrootn_storage_to_fire;   /* (kgN/m2/d) */
    double          m_deadcrootn_storage_to_fire;   /* (kgN/m2/d) */
    double          m_leafn_transfer_to_fire;   /* (kgN/m2/d) */
    double          m_frootn_transfer_to_fire;  /* (kgN/m2/d) */
    double          m_livestemn_transfer_to_fire;   /* (kgN/m2/d) */
    double          m_deadstemn_transfer_to_fire;   /* (kgN/m2/d) */
    double          m_livecrootn_transfer_to_fire;  /* (kgN/m2/d) */
    double          m_deadcrootn_transfer_to_fire;  /* (kgN/m2/d) */
    double          m_livestemn_to_fire;    /* (kgN/m2/d) */
    double          m_deadstemn_to_fire;    /* (kgN/m2/d) */
    double          m_livecrootn_to_fire;   /* (kgN/m2/d) */
    double          m_deadcrootn_to_fire;   /* (kgN/m2/d) */
    double          m_retransn_to_fire; /* (kgN/m2/d) */
    double          m_litr1n_to_fire;   /* (kgN/m2/d) */
    double          m_litr2n_to_fire;   /* (kgN/m2/d) */
    double          m_litr3n_to_fire;   /* (kgN/m2/d) */
    double          m_litr4n_to_fire;   /* (kgN/m2/d) */
    double          m_cwdn_to_fire; /* (kgN/m2/d) */
    /* phenology fluxes from transfer pool */
    double          leafn_transfer_to_leafn;    /* (kgN/m2/d) */
    double          frootn_transfer_to_frootn;  /* (kgN/m2/d) */
    double          livestemn_transfer_to_livestemn;    /* (kgN/m2/d) */
    double          deadstemn_transfer_to_deadstemn;    /* (kgN/m2/d) */
    double          livecrootn_transfer_to_livecrootn;  /* (kgN/m2/d) */
    double          deadcrootn_transfer_to_deadcrootn;  /* (kgN/m2/d) */
    /* litterfall fluxes */
    double          leafn_to_litr1n;    /* (kgN/m2/d) */
    double          leafn_to_litr2n;    /* (kgN/m2/d) */
    double          leafn_to_litr3n;    /* (kgN/m2/d) */
    double          leafn_to_litr4n;    /* (kgN/m2/d) */
    double          leafn_to_retransn;  /* (kgN/m2/d) */
    double          frootn_to_litr1n;   /* (kgN/m2/d) */
    double          frootn_to_litr2n;   /* (kgN/m2/d) */
    double          frootn_to_litr3n;   /* (kgN/m2/d) */
    double          frootn_to_litr4n;   /* (kgN/m2/d) */
    /* deposition flux */
    double          ndep_to_sminn;  /* (kgN/m2/d) */
    double          nfix_to_sminn;  /* (kgN/m2/d) */
    /* litter and soil decomposition fluxes */
    double          cwdn_to_litr2n; /* (kgN/m2/d) */
    double          cwdn_to_litr3n; /* (kgN/m2/d) */
    double          cwdn_to_litr4n; /* (kgN/m2/d) */
    double          litr1n_to_soil1n;   /* (kgN/m2/d) */
    double          sminn_to_soil1n_l1; /* (kgN/m2/d) */
    double          litr2n_to_soil2n;   /* (kgN/m2/d) */
    double          sminn_to_soil2n_l2; /* (kgN/m2/d) */
    double          litr3n_to_litr2n;   /* (kgN/m2/d) */
    double          litr4n_to_soil3n;   /* (kgN/m2/d) */
    double          sminn_to_soil3n_l4; /* (kgN/m2/d) */
    double          soil1n_to_soil2n;   /* (kgN/m2/d) */
    double          sminn_to_soil2n_s1; /* (kgN/m2/d) */
    double          soil2n_to_soil3n;   /* (kgN/m2/d) */
    double          sminn_to_soil3n_s2; /* (kgN/m2/d) */
    double          soil3n_to_soil4n;   /* (kgN/m2/d) */
    double          sminn_to_soil4n_s3; /* (kgN/m2/d) */
    double          soil4n_to_sminn;    /* (kgN/m2/d) */
    /* denitrification (volatilization) fluxes */
    double          sminn_to_nvol_l1s1; /* (kgN/m2/d) */
    double          sminn_to_nvol_l2s2; /* (kgN/m2/d) */
    double          sminn_to_nvol_l4s3; /* (kgN/m2/d) */
    double          sminn_to_nvol_s1s2; /* (kgN/m2/d) */
    double          sminn_to_nvol_s2s3; /* (kgN/m2/d) */
    double          sminn_to_nvol_s3s4; /* (kgN/m2/d) */
    double          sminn_to_nvol_s4;   /* (kgN/m2/d) */
    double          sminn_to_denitrif;  /* (kgN/m2/d) */

    /* leaching flux */
    double          sminn_leached;  /* (kgN/m2/d) */
    /* daily allocation fluxes */
    double          retransn_to_npool;  /* (kgN/m2/d) */
    double          sminn_to_npool; /* (kgN/m2/d) */
    double          npool_to_leafn; /* (kgN/m2/d) */
    double          npool_to_leafn_storage; /* (kgN/m2/d) */
    double          npool_to_frootn;    /* (kgN/m2/d) */
    double          npool_to_frootn_storage;    /* (kgN/m2/d) */
    double          npool_to_livestemn; /* (kgN/m2/d) */
    double          npool_to_livestemn_storage; /* (kgN/m2/d) */
    double          npool_to_deadstemn; /* (kgN/m2/d) */
    double          npool_to_deadstemn_storage; /* (kgN/m2/d) */
    double          npool_to_livecrootn;    /* (kgN/m2/d) */
    double          npool_to_livecrootn_storage;    /* (kgN/m2/d) */
    double          npool_to_deadcrootn;    /* (kgN/m2/d) */
    double          npool_to_deadcrootn_storage;    /* (kgN/m2/d) */
    /* annual turnover of storage to transfer */
    double          leafn_storage_to_leafn_transfer;    /* (kgN/m2/d) */
    double          frootn_storage_to_frootn_transfer;  /* (kgN/m2/d) */
    double          livestemn_storage_to_livestemn_transfer;    /* (kgN/m2/d) */
    double          deadstemn_storage_to_deadstemn_transfer;    /* (kgN/m2/d) */
    double          livecrootn_storage_to_livecrootn_transfer;  /* (kgN/m2/d) */
    double          deadcrootn_storage_to_deadcrootn_transfer;  /* (kgN/m2/d) */
    /* turnover of live wood to dead wood, with retranslocation */
    double          livestemn_to_deadstemn; /* (kgN/m2/d) */
    double          livestemn_to_retransn;  /* (kgN/m2/d) */
    double          livecrootn_to_deadcrootn;   /* (kgN/m2/d) */
    double          livecrootn_to_retransn; /* (kgN/m2/d) */
} nflux_struct;

/* temporary nitrogen variables for reconciliation of decomposition
 * immobilization fluxes and plant growth N demands */
typedef struct
{
    double          mineralized;
    double          potential_immob;
    double          plitr1c_loss;
    double          pmnf_l1s1;
    double          plitr2c_loss;
    double          pmnf_l2s2;
    double          plitr4c_loss;
    double          pmnf_l4s3;
    double          psoil1c_loss;
    double          pmnf_s1s2;
    double          psoil2c_loss;
    double          pmnf_s2s3;
    double          psoil3c_loss;
    double          pmnf_s3s4;
    double          psoil4c_loss;
    double          kl4;
} ntemp_struct;

/* phenological control arrays */
typedef struct
{
    int            *remdays_curgrowth;  /* (nmetdays) days left in current growth season */
    int            *remdays_transfer;   /* (nmetdays) number of transfer days remaining */
    int            *remdays_litfall;    /* (nmetdays) number of litfall days remaining */
    int            *predays_transfer;   /* (nmetdays) number of transfer days previous */
    int            *predays_litfall;    /* (nmetdays) number of litfall days previous */
} phenarray_struct;

/* daily phenological data array */
typedef struct
{
    double          remdays_curgrowth;  /* days left in current growth season */
    double          remdays_transfer;   /* number of transfer days remaining */
    double          remdays_litfall;    /* number of litfall days remaining */
    double          predays_transfer;   /* number of transfer days previous */
    double          predays_litfall;    /* number of litfall days previous */
} phenology_struct;

/* ecophysiological variables */
typedef struct
{
    double          day_leafc_litfall_increment;    /* (kgC/m2/d) rate leaf litfall */
    double          day_frootc_litfall_increment;   /* (kgC/m2/d) rate froot litfall */
    double          day_livestemc_turnover_increment;   /* (kgC/m2/d) rate livestem turnover */
    double          day_livecrootc_turnover_increment;  /* (kgC/m2/d) rate livecroot turnover */
    double          annmax_leafc;   /* (kgC/m2) annual maximum daily leaf C */
    double          annmax_frootc;  /* (kgC/m2) annual maximum daily froot C */
    double          annmax_livestemc;   /* (kgC/m2) annual maximum daily livestem C */
    double          annmax_livecrootc;  /* (kgC/m2) annual maximum daily livecroot C */
    double          dsr;        /* (days) number of days since rain, for soil evap */
    double          proj_lai;   /* (DIM) live projected leaf area index */
    double          all_lai;    /* (DIM) live all-sided leaf area index */
    double          plaisun;    /* (DIM) sunlit projected leaf area index */
    double          plaishade;  /* (DIM) shaded projected leaf area index */
    double          sun_proj_sla;   /* (m2/kgC) sunlit projected SLA */
    double          shade_proj_sla; /* (m2/kgC) shaded projected SLA */
    double          psi;        /* (MPa) water potential of soil and leaves */
    double          vwc;        /* (DIM) volumetric water content */
    double          dlmr_area_sun;  /* (umolC/m2projected leaf area/s) sunlit leaf MR */
    double          dlmr_area_shade;    /* (umolC/m2projected leaf area/s) shaded leaf MR */
    double          gl_t_wv_sun;    /* (m/s) leaf-scale conductance to transpired water */
    double          gl_t_wv_shade;  /* (m/s) leaf-scale conductance to transpired water */
    double          assim_sun;  /* (umol/m2/s) sunlit assimilation per unit pLAI */
    double          assim_shade;    /* (umol/m2/s) shaded assimilation per unit pLAI */
    /* decomp variables */
    double          t_scalar;   /* (DIM) decomp temperature scalar */
    double          w_scalar;   /* (DIM) decomp water scalar */
    double          rate_scalar;    /* (DIM) decomp combined scalar */
    double          daily_gross_nmin;   /* (kgN/m2/d) daily gross N mineralization */
    double          daily_gross_nimmob; /* (kgN/m2/d) daily gross N immobilization */
    double          daily_net_nmin; /* (kgN/m2/d) daily net N mineralization */
    double          fpi;        /* (DIM) fraction of potential immobilization */

    /* the following are optional outputs, usually set if the appropriate
     * functions are called with the flag verbose = 1 */
    double          m_tmin;     /* (DIM) freezing night temperature multiplier */
    double          m_psi;      /* (DIM) water potential multiplier */
    double          m_co2;      /* (DIM) atmospheric [CO2] multiplier */
    double          m_ppfd_sun; /* (DIM) PAR flux density multiplier */
    double          m_ppfd_shade;   /* (DIM) PAR flux density multiplier */
    double          m_vpd;      /* (DIM) vapor pressure deficit multiplier */
    double          m_final_sun;    /* (DIM) product of all other multipliers */
    double          m_final_shade;  /* (DIM) product of all other multipliers */
    double          gl_bl;      /* (m/s) leaf boundary layer conductance */
    double          gl_c;       /* (m/s) leaf cuticular conductance */
    double          gl_s_sun;   /* (m/s) leaf-scale stomatal conductance */
    double          gl_s_shade; /* (m/s) leaf-scale stomatal conductance */
    double          gl_e_wv;    /* (m/s) leaf conductance to evaporated water */
    double          gl_sh;      /* (m/s) leaf conductance to sensible heat */
    double          gc_e_wv;    /* (m/s) canopy conductance to evaporated water */
    double          gc_sh;      /* (m/s) canopy conductance to sensible heat */

    /* diagnostic variables for ouput purposes only */
    double          ytd_maxplai;    /* (DIM) year-to-date maximum projected LAI */

    /* Variables below are added for PIHM-BGC */
    double          dormant_flag;   /* dormancy flag */
    double          days_active;    /* number of days since last dormancy */
    double          onset_flag; /* onset flag */
    double          onset_counter;  /* onset days counter */
    double          onset_gddflag;  /* onset flag for growing degree day sum */
    double          onset_fdd;  /* onset freezing degree days counter */
    double          onset_gdd;  /* onset growing degree days */
    double          onset_swi;  /* onset soil water index */
    double          offset_flag;    /* offset flag */
    double          offset_counter; /* offset days counter */
    double          offset_fdd; /* offset freezing degree days counter */
    double          offset_swi; /* offset soil water index */
    double          lgsf;       /* long growing season factor [0-1] */
    double          bglfr;      /* background litterfall rate (1/s) */
    double          bgtr;       /* background transfer growth rate (1/s) */
    //   double dayl;     /* daylength (seconds) */
    double          annavg_t2m; /* annual average 2m air temperature (K) */
    double          tempavg_t2m;    /* temporary average 2m air temperature (K) */
    double          gpp;        /* GPP flux before downregulation (gC/m2/s) */
    double          availc;     /* C flux available for allocation (gC/m2/s) */
    double          xsmrpool_recover;   /* C flux assigned to recovery of negative cpool (gC/m2/s) */
    double          xsmrpool_c13ratio;  /* C13/C(12+13) ratio for xsmrpool (proportion) */
    double          alloc_pnow; /* fraction of current allocation to display as new growth (DIM) */
    double          c_allometry;    /* C allocation index (DIM) */
    double          n_allometry;    /* N allocation index (DIM) */
    double          plant_ndemand;  /* N flux required to support initial GPP (gN/m2/s) */
    double          tempsum_potential_gpp;  /* temporary annual sum of potential GPP */
    double          annsum_potential_gpp;   /* annual sum of potential GPP */
    double          tempmax_retransn;   /* temporary annual max of retranslocated N pool (gN/m2) */
    double          annmax_retransn;    /* annual max of retranslocated N pool (gN/m2) */
    double          avail_retransn; /* N flux available from retranslocation pool (gN/m2/s) */
    double          plant_nalloc;   /* total allocated N flux (gN/m2/s) */
    double          plant_calloc;   /* total allocated C flux (gC/m2/s) */
    double          excess_cflux;   /* C flux not allocated due to downregulation (gC/m2/s) */
    double          downreg;    /* fractional reduction in GPP due to N limitation (DIM) */
    double          prev_leafc_to_litter;   /* previous timestep leaf C litterfall flux (gC/m2/s) */
    double          prev_frootc_to_litter;  /* previous timestep froot C litterfall flux (gC/m2/s) */
    double          tempsum_npp;    /* temporary annual sum of NPP (gC/m2/yr) */
    double          annsum_npp; /* annual sum of NPP (gC/m2/yr) */
    double          tempsum_litfall;    /* temporary annual sum of litfall (gC/m2/yr) */
    double          annsum_litfall; /* annual sum of litfall (gC/m2/yr) */
    double          rc13_canair;    /* C13O2/C12O2 in canopy air */
    double          rc13_psnsun;    /* C13O2/C12O2 in sunlit canopy psn flux */
    double          rc13_psnsha;    /* C13O2/C12O2 in shaded canopy psn flux */

    double          old_c_balance;
    double          old_n_balance;
} epvar_struct;

/* soil and site constants */
typedef struct
{
    //    double          soil_depth; /* (m)   effective depth of rooting zone */
    //    double          soil_b;     /* (DIM) Clapp-Hornberger "b" parameter */
    double          soil_alpha; /* van Genuchten Alpha (m-1) */
    double          soil_beta;  /* van Genuchten Beta (-) */
    double          vwc_sat;    /* (DIM) volumetric water content at saturation */
    double          vwc_min;
    double          vwc_fc;     /* (DIM) VWC at field capacity ( = -0.015 MPa) */
    //    double          psi_sat;    /* (MPa) soil matric potential at saturation */
    //    double          soilw_sat;  /* (kgH2O/m2) soilwater at saturation */
    //    double          soilw_fc;   /* (kgH2O/m2) soilwater at field capacity */
    //    double          elev;       /* (m) site elevation */
    double          lon;
    double          lat;        /* (degrees) site latitude (negative for south) */
    double          sw_alb;     /* (DIM) surface shortwave albedo */
    //    double          ndep;       /* (kgN/m2/yr) wet+dry atmospheric deposition of N */
    //    double          nfix;       /* (kgN/m2/yr) symbiotic+asymbiotic fixation of N */
} siteconst_struct;

/* canopy ecophysiological constants */
typedef struct
{
    int             woody;      /* (flag) 1=woody, 0=non-woody */
    int             evergreen;  /* (flag) 1=evergreen, 0=deciduous */
    int             c3_flag;    /* (flag) 1 = C3,  0 = C4 */
    int             phenology_flag; /* (flag) 1=phenology model, 0=user defined */
    int             onday;      /* (yday) yearday leaves on */
    int             offday;     /* (yday) yearday leaves off */
    double          transfer_days;  /* (prop.) fraction of growth period for transfer */
    double          litfall_days;   /* (prop.) fraction of growth period for litfall */
    double          leaf_turnover;  /* (1/yr) annual leaf turnover fraction */
    double          froot_turnover; /* (1/yr) annual fine root turnover fraction */
    double          livewood_turnover;  /* (1/yr) annual live wood turnover fraction */
    double          daily_mortality_turnover;   /* (1/day) daily mortality turnover */
    double          daily_fire_turnover;    /* (1/day) daily fire turnover */
    double          alloc_frootc_leafc; /* (ratio) new fine root C to new leaf C */
    double          alloc_newstemc_newleafc;    /* (ratio) new stem C to new leaf C */
    double          alloc_newlivewoodc_newwoodc;    /* (ratio) new livewood C:new wood C */
    double          alloc_crootc_stemc; /* (ratio) new live croot C to new live stem C */
    double          alloc_prop_curgrowth;   /* (prop.) daily allocation to current growth */
    double          avg_proj_sla;   /* (m2/kgC) canopy average proj. SLA */
    double          sla_ratio;  /* (DIM) ratio of shaded to sunlit projected SLA */
    double          lai_ratio;  /* (DIM) ratio of (all-sided LA / one-sided LA) */
    double          int_coef;   /* (kg/kg/LAI/d) canopy precip interception coef */
    double          ext_coef;   /* (DIM) canopy light extinction coefficient */
    double          flnr;       /* (kg NRub/kg Nleaf) leaf N in Rubisco */
    double          psi_open;   /* (MPa) psi at start of conductance reduction */
    double          psi_close;  /* (MPa) psi at complete conductance reduction */
    double          vpd_open;   /* (Pa)  vpd at start of conductance reduction */
    double          vpd_close;  /* (Pa)  vpd at complete conductance reduction */
    double          gl_smax;    /* (m/s) maximum leaf-scale stomatal conductance */
    double          gl_c;       /* (m/s) leaf-scale cuticular conductance */
    double          gl_bl;      /* (m/s) leaf-scale boundary layer conductance */
    double          froot_cn;   /* (kgC/kgN) C:N for fine roots */
    double          leaf_cn;    /* (kgC/kgN) C:N for leaves */
    double          livewood_cn;    /* (kgC/kgN) C:N for live wood */
    double          deadwood_cn;    /* (kgC/kgN) C:N for dead wood */
    double          leaflitr_cn;    /* (kgC/kgN) constant C:N for leaf litter */
    double          leaflitr_flab;  /* (DIM) leaf litter labile fraction */
    double          leaflitr_fucel; /* (DIM) leaf litter unshielded cellulose fract. */
    double          leaflitr_fscel; /* (DIM) leaf litter shielded cellulose fract. */
    double          leaflitr_flig;  /* (DIM) leaf litter lignin fraction */
    double          frootlitr_flab; /* (DIM) froot litter labile fraction */
    double          frootlitr_fucel;    /* (DIM) froot litter unshielded cellulose fract */
    double          frootlitr_fscel;    /* (DIM) froot litter shielded cellulose fract */
    double          frootlitr_flig; /* (DIM) froot litter lignin fraction */
    double          deadwood_fucel; /* (DIM) dead wood unshileded cellulose fraction */
    double          deadwood_fscel; /* (DIM) dead wood shielded cellulose fraction */
    double          deadwood_flig;  /* (DIM) dead wood lignin fraction */
} epconst_struct;

/* structure for the photosynthesis routine */
typedef struct
{
    int             c3;         /* (flag) set to 1 for C3 model, 0 for C4 model */
    double          pa;         /* (Pa) atmospheric pressure */
    double          co2;        /* (ppm) atmospheric [CO2] */
    double          t;          /* (deg C) temperature */
    double          lnc;        /* (kg Nleaf/m2) leaf N per unit sunlit leaf area */
    double          flnr;       /* (kg NRub/kg Nleaf) fract. of leaf N in Rubisco */
    double          ppfd;       /* (umol/m2/s) PAR flux per unit sunlit leaf area */
    double          g;          /* (umol/m2/s/Pa) conductance to CO2 */
    double          dlmr;       /* (umol/m2/s) day leaf m. resp, proj. area basis */
    double          Ci;         /* (Pa) intercellular [CO2] */
    double          O2;         /* (Pa) atmospheric [O2] */
    double          Ca;         /* (Pa) atmospheric [CO2] */
    double          gamma;      /* (Pa) CO2 compensation point, no Rd */
    double          Kc;         /* (Pa) MM constant carboxylation */
    double          Ko;         /* (Pa) MM constant oxygenation */
    double          Vmax;       /* (umol/m2/s) max rate carboxylation */
    double          Jmax;       /* (umol/m2/s) max rate electron transport */
    double          J;          /* (umol/m2/s) rate of RuBP regeneration */
    double          Av;         /* (umol/m2/s) carboxylation limited assimilation */
    double          Aj;         /* (umol/m2/s) RuBP regen limited assimilation */
    double          A;          /* (umol/m2/s) final assimilation rate */
} psn_struct;

typedef struct
{
    double          ta;         /* (degC) air temperature */
    double          pa;         /* (Pa)   air pressure */
    double          vpd;        /* (Pa)   vapor pressure deficit */
    double          irad;       /* (W/m2) incident shortwave flux density */
    double          rv;         /* (s/m)  resistance to water vapor flux */
    double          rh;         /* (s/m)  resistance to sensible heat flux */
} pmet_struct;

typedef struct
{
    double          daily_npp;  /* kgC/m2/day = GPP - Rmaint - Rgrowth */
    double          daily_nep;  /* kgC/m2/day = NPP - Rheterotroph */
    double          daily_nee;  /* kgC/m2/day = NEP - fire losses */
    double          daily_gpp;  /* kgC/m2/day  gross PSN source */
    double          daily_mr;   /* kgC/m2/day  maintenance respiration */
    double          daily_gr;   /* kgC/m2/day  growth respiration */
    double          daily_hr;   /* kgC/m2/day  heterotrophic respiration */
    double          daily_fire; /* kgC/m2/day  fire losses */
    double          daily_litfallc; /* kgC/m2/day  total litterfall */
    double          daily_et;   /* kgW/m2/day daily evapotranspiration */
    double          daily_evap; /* kgW/m2/day daily evaporation */
    double          daily_trans;    /* kgW/m2/day daily transpiration */
    double          daily_outflow;  /* kgW/m2/day daily outflow */
    double          daily_soilw;    /* kgW/m2/day daily soilw */
    double          daily_snoww;    /* kgW/m2/day daily snoww */
    double          cum_npp;    /* kgC/m2  Summed over entire simulation */
    double          cum_nep;    /* kgC/m2  Summed over entire simulation */
    double          cum_nee;    /* kgC/m2  Summed over entire simulation */
    double          cum_gpp;    /* kgC/m2  Summed over entire simulation */
    double          cum_mr;     /* kgC/m2  Summed over entire simulation */
    double          cum_gr;     /* kgC/m2  Summed over entire simulation */
    double          cum_hr;     /* kgC/m2  Summed over entire simulation */
    double          cum_fire;   /* kgC/m2  Summed over entire simulation */
    double          vegc;       /* kgC/m2  total vegetation C */
    double          litrc;      /* kgC/m2  total litter C */
    double          soilc;      /* kgC/m2  total soil C */
    double          totalc;     /* kgC/m2  total of vegc, litrc, and soilc */
} summary_struct;

/* restart data structure */
typedef struct
{
    double          soilw;
    double          snoww;
    double          canopyw;
    double          leafc;
    double          leafc_storage;
    double          leafc_transfer;
    double          frootc;
    double          frootc_storage;
    double          frootc_transfer;
    double          livestemc;
    double          livestemc_storage;
    double          livestemc_transfer;
    double          deadstemc;
    double          deadstemc_storage;
    double          deadstemc_transfer;
    double          livecrootc;
    double          livecrootc_storage;
    double          livecrootc_transfer;
    double          deadcrootc;
    double          deadcrootc_storage;
    double          deadcrootc_transfer;
    double          gresp_storage;
    double          gresp_transfer;
    double          cwdc;
    double          litr1c;
    double          litr2c;
    double          litr3c;
    double          litr4c;
    double          soil1c;
    double          soil2c;
    double          soil3c;
    double          soil4c;
    double          cpool;
    double          leafn;
    double          leafn_storage;
    double          leafn_transfer;
    double          frootn;
    double          frootn_storage;
    double          frootn_transfer;
    double          livestemn;
    double          livestemn_storage;
    double          livestemn_transfer;
    double          deadstemn;
    double          deadstemn_storage;
    double          deadstemn_transfer;
    double          livecrootn;
    double          livecrootn_storage;
    double          livecrootn_transfer;
    double          deadcrootn;
    double          deadcrootn_storage;
    double          deadcrootn_transfer;
    double          cwdn;
    double          litr1n;
    double          litr2n;
    double          litr3n;
    double          litr4n;
    double          soil1n;
    double          soil2n;
    double          soil3n;
    double          soil4n;
    double          sminn;
    double          retransn;
    double          npool;
    double          day_leafc_litfall_increment;
    double          day_frootc_litfall_increment;
    double          day_livestemc_turnover_increment;
    double          day_livecrootc_turnover_increment;
    double          annmax_leafc;
    double          annmax_frootc;
    double          annmax_livestemc;
    double          annmax_livecrootc;
    double          dsr;
    double          dormant_flag;
    double          onset_flag;
    double          onset_counter;
    double          onset_gddflag;
    double          onset_fdd;
    double          onset_gdd;
    double          onset_swi;
    double          offset_flag;
    double          offset_counter;
    double          offset_fdd;
    double          offset_swi;
    //    int             metyr;
} restart_data_struct;

typedef struct epclist_struct
{
    int             nvegtypes;  /* number of vegetation types */
    epconst_struct *epc;        /* pointer to array of epc structures */
} epclist_struct;


typedef struct bgc_grid
{
    siteconst_struct sitec;     /* site constants */
    metarr_struct   metarr;     /* meteorological data array */
    metvar_struct   metv;
    wstate_struct   ws;         /* water state variables */
    wflux_struct    wf;
    cinit_struct    cinit;      /* first-year values for leafc and stemc */
    cstate_struct   cs;         /* carbon state variables */
    cflux_struct    cf;
    nstate_struct   ns;         /* nitrogen state variables */
    nflux_struct    nf;
    psn_struct      psn_sun;
    psn_struct      psn_shade;
    ntemp_struct    nt;
    summary_struct  summary;

    phenology_struct phen;

    epconst_struct  epc;        /* ecophysiological constants */
    epvar_struct    epv;
    restart_data_struct restart_input;  /* input restart data */
    restart_data_struct restart_output;   /* output restart data */

} bgc_grid;

typedef struct bgc_struct
{
    bgc_grid       *grid;
    control_struct  ctrl;       /* bgc control variables */
    //    ramp_ndep_struct ramp_ndep; /* ramped Ndep information */
    co2control_struct co2;      /* CO2 concentration information */
    ndepcontrol_struct ndepctrl;    /* Nitrogen deposition control structure */
    //    siteconst_struct sitec;     /* site constants */
    epclist_struct  epclist;
    double          spinup_resid_trend; /* kgC/m2/yr remaining trend after spinup */
    int             spinup_years;   /* number of years before reaching steady-state */
    unsigned char   bgc_ascii;  /* ASCII output flag */
    TSD           **Forcing;
}              *bgc_struct;

#endif
