/*
 * SYSTEM REGISTER.h
 *
 *  Created on: 10/04/2024
 *      Author: Harold Gómez
 */

#ifndef SYSTEM_REGISTER_H_
#define SYSTEM_REGISTER_H_
#include <stdint.h>


//-------HP_SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG (0x0000)-------------------//

enum {
    mHP_SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT = 0x00000001U,
    mHP_SYSTEM_ENABLE_DOWNLOAD_G0CB_DECRYPT = 0x00000004U,
    mHP_SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT = 0x00000008U,
};

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t SPI_MANUAL_ENCRYPT                 :1; // Configures whether or not to enable MSPI XT manual encryption in SPI boot mode.
        uint32_t                                    :1; //Reserved
        uint32_t DOWNLOAD_G0CB_DECRYPT              :1; // Configures whether or not to enable MSPI XTS auto decryption in download boot mode.
        uint32_t DOWNLOAD_MANUAL_ENCRYPT            :1; //Configures whether or not to enable MSPI XTS manual encryption in download boot mode.
        uint32_t                                    :28; //Reserved
    }BITS;
}__HP_SYSTEM_EXTERNAL_t;



//-----------------HP_SYSTEM_SEC_DPA_CONF_REG (0x0008)--------//

#define mHP_SYSTEM_DPA_LEVEL 0x000000011U //Mascara para posiciones.

enum{
    kSEC_DPA_OFF, // Security level 0
    kSEC_DPA_LOW,// Security level 1
    kSEC_DPA_MIDDLE,//Security level 2
    kSEC_DPA_HIGH,//Security level 3    
};

enum{
    mHP_SYSTEM_SEC_DPA_CGF_SEL= 0x00000004U,
}; 



typedef union{
    uint32_t WORD;      //Access to whole Register
    struct{
        uint32_t SEC_DPA_LEVEL            :2; // Configures whether or not to enable anti-DPA attack. Valid only when HP_SYSTEM_SEC_DPA_CFG_SEL is 0.
        uint32_t SEC_DPA_CFG_SEL          :1; //Configures whether to select HP_SYSTEM_SEC_DPA_LEVEL or EFUSE_SEC_DPA_LEVEL (from eFuse) to control DPA level.
        uint32_t                          :29; //Reserved
    }BITS;
}__SEC_DPA_CONF_t;




//------HP_SYSTEM_ROM_TABLE_LOCK_REG (0x0038)-------//

enum{
    mHP_SYSTEM_TABLE_LOCK = 0x00000001U
};

typedef union {
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t TABLE_LOCK             :1; // Configures whether or not to lock the value contained in HP_SYSTEM_ROM_TABLE.
        uint32_t                        :31; //Reserved.
    }BITS;
    
}__HP_SYSTEM_ROM_TABLE_LOCK_t;


//---------------HP_SYSTEM_ROM_TABLE_REG (0x003C)----------//
        uint32_t TABLE_REG; //Software ROM-Table register, whose content can be modified only when HP_SYSTEM_ROM_TABLE_LOCK is 0.


//------------------HP_SYSTEM_CORE_DEBUG_RUNSTALL_CONF_REG (0x0040)----//
enum{
    mHP_SYSTEM_CORE_DEBUG_RUNSTALL_ENABLE = 0x00000001U
};

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t DEBUG_RUNSTALL_ENABLE            :1; //Configures whether or not to enable debug RunStall functionality between HP CPU and LP CPU.
        uint32_t                                  :31; //Reserved.
    }BITS;

}__CORE_DEBUG_RUNSTALL_CONF_REG_t;



//-------------------------DEFINICION CPU Peripheral Timeout Register-------------------------//



//-------------HP_SYSTEM_CPU_PERI_TIMEOUT_CONF_REG (0x000C)//---------

#define mHP_SYSTEM_CPU_PERI_THRES 0x0000FFFFU
enum{
    mHP_SYSTEM_CPU_PERI_TIMEOUT_INT_CLEAR = 0x00000001U<<16,
    mHP_SYSTEM_CPU_PERI_TIMEOUT_PROTECT_EN =0x00000001U<<17
};

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t CPU_PERI_TIMEOUT_THRES              :16; // Configures the timeout threshold for bus access for accessing CPU peripheral register in the number of clock cycles of the clock domain.
        uint32_t CPU_PERI_TIMEOUT_INT_CLEAR          :1; //Write 1 to clear timeout interrupt.
        uint32_t CPU_PERI_TIMEOUT_PROTECT_EN         :1; //Configures whether or not to enable timeout protection for accessing CPU peripheral registers.
    }BITS;
}__PERI_TIMEOUT_CONF_REG_t;



//---------------HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG (0x0010)-------//

    uint32_t TIMEOUT_ADDR; // Represents the address information of abnormal access. 

//---------------HP_SYSTEM_CPU_PERI_TIMEOUT_UID_REG (0x0014)-------//

#define mHP_SYSTEM_CPU_PERI_TIMEOUT_UID 0x0000003FU
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t TIMEOUT_UID           :7; //  Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared
        uint32_t                      :25; //Reserved

    }BITS;
}__PERI_TIMEOUT_UID_t;


//-------------------------DEFINICION HP Peripheral Timeout Register-------------------------//


//-------------//HP_SYSTEM_HP_PERI_TIMEOUT_CONF_REG (0x0018)---------//
#define mHP_SYSTEM_HP_PERI_TIMEOUT_THRES 0x0000FFFFU

enum {
    mHP_PERI_TIMEOUT_INT_CLEAR = 0x00000001U<<16,
    mHP_PERI_TIMEOUT_PROTECT_EN = 0x00000001U<<17

};
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_THRES             :16; // Configures the timeout threshold for bus access for accessing HP peripheral register, corresponding to the number of clock cycles of the clock domain.
        uint32_t HP_PERI_TIMEOUT_INT_CLEAR         :1; //configures whether or not to clear timeout interrupt.
        uint32_t HP_PERI_TIMEOUT_PROTECT_EN        :1; //Configures whether or not to enable timeout protection for accessing HP peripheral registers.
        uint32_t                                  :14; //Reserved
    }BITS;
}__HP_TIMEOUT_CONF_REG_t;

//---------------------HP_SYSTEM_HP_PERI_TIMEOUT_ADDR_REG (0x001C)----//


    uint32_t HP_PERI_TIMEOUT_ADDR_REG; // Represents the address information of abnormal access.


// HP_SYSTEM_HP_PERI_TIMEOUT_UID_REG (0x0020)

#define mHP_SYSTEM_TIMEOUT_UID_REG 0x0000003FU

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_UID          :7; // Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared.
        uint32_t                               :25; //Reserved
    }BITS;
}__HP_PERI_TIMEOUT_UID_t;


//-------------------------DEFINICION LP Peripheral Timeout Register-------------------------//



//----------------------------LP_PERI_BUS_TIMEOUT_CONF_REG (0x0010)----------------------------//
#define mLP_PERI_BUS_TIMEOUT_THRES 0x0000FFFFU
enum{
    mBUS_TIME_OUT_INT_CLEAR = 0x00000001U<<16,
    mBUS_TIME_OUT_PROTECT_EN = 0x00000001U<<17
};

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_THRES             :16; // Configures the timeout threshold for bus access for accessing LP peripheral register, corresponding to the number of clock cycles of the clock domain.
        uint32_t LP_PERI_TIMEOUT_INT_CLEAR         :1; //configures whether or not to clear timeout interrupt.
        uint32_t LP_PERI_TIMEOUT_PROTECT_EN        :1; //Configures whether or not to enable timeout protection for accessing LP peripheral registers.
        uint32_t                                  :14; //Reserved
    }BITS;
}__BUS_TIMEOUT_CONF_REG_t;

//---------------------------------------LP_PERI_BUS_TIMEOUT_ADDR_REG (0x0014)------------//
        uint32_t LP_PERI_TIMEOUT_ADDR;

//-------------------------------LP_PERI_BUS_TIMEOUT_UID_REG (0x0018)----------------------------//

#define mLP_PERI_BUS_TIMEOUT_UID 0x0000007FU
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_UID          :7; // Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared.
        uint32_t                               :25; //Reserved
    }BITS;
}__TIME_OUT_UID_REG_t;
//-------------------------DEFINICION Version Register-------------------------//


//------------------------ HP_SYSTEM_DATE_REG (0x03FC)--------------------- //
#define mSYSTEM_DATE 0x0FFFFFFFU
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t SYSTEM_DATE          :28; //Version control register.
        uint32_t                        :4; //Reserved
    }BITS;
}__DATE_REG_t;


//------DEFINICION------//
typedef struct {
    volatile __HP_SYSTEM_EXTERNAL_t EXTERNAL;
    volatile __SEC_DPA_CONF_t CONFREG;
    volatile __HP_SYSTEM_ROM_TABLE_LOCK_t LOCKREG;
    volatile __CORE_DEBUG_RUNSTALL_CONF_REG_t RUNSTALLEN;
    volatile __PERI_TIMEOUT_CONF_REG_t PERICONFREG;
    volatile __PERI_TIMEOUT_UID_t PERIUIDREG;
    volatile __HP_TIMEOUT_CONF_REG_t HPCONF;
    volatile __HP_PERI_TIMEOUT_UID_t HPUID;
    volatile __BUS_TIMEOUT_CONF_REG_t BUSCONF;
    volatile __TIME_OUT_UID_REG_t BUSUID;
    volatile __DATE_REG_t DATE;
}__HP_SYSREG_t;

#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x60095000))

#define rHP_SYSTEM_EXTERNAL sHP_SYSREG.EXTERNAL.WORD
#define bHP_SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT sHP_SYSREG.EXTERNAL.BITS.SPI_MANUAL_ENCRYPT
#define bHP_SYSTEM_ENABLE_DOWNLOAD_G0CB_DECRYPT sHP_SYSREG.EXTERNAL.BITS.DOWNLOAD_G0CB_DECRYPT
#define bHP_SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT sHP_SYSREG.EXTERNAL.BITS.DOWNLOAD_MANUAL_ENCRYPT



#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x60095008))

#define rSEC_DPA_CONF sHP_SYSREG.CONFREG.WORD
#define bHP_SYSTEM_DPA_LEVEL sHP_SYSREG.CONFREG.BITS.SEC_DPA_LEVEL
#define bHP_HP_SYSTEM_SEC_DPA_CGF_SEL sHPSYSREG.CONFREG.BITS.SEC_DPA_CFG_SEL
//12
#define rPERI_TIMEOUT_CONF_REG sHP_SYSREG.PERICONFREG.WORD
#define bHP_SYSTEM_CPU_PERI_THRES sHP_SYSREG.PERICONFREG.BITS.CPU_PERI_TIMEOUT_THRES
#define bHP_SYSTEM_CPU_PERI_TIMEOUT_INT_CLEAR sHP_SYSREG.PERICONFREG.BITS.CPU_PERI_TIMEOUT_INT_CLEAR
#define bHP_SYSTEM_CPU_PERI_TIMEOUT_PROTECT_EN sHP_SYSREG.PERICONFREG.BITS.CPU_PERI_TIMEOUT_PROTECT_EN
//16
#define rTIMEOUT_ADDR
//20
#define rPERI_TIMEOUT_UID sHP_SYSREG.PERIUIDREG.WORD
#define bHP_SYSTEM_CPU_PERI_TIMEOUT_UID sHP_SYSREG.PERIUIDREG.BITS.TIMEOUT_UID
//24
#define rHP_TIMEOUT_CONF_REG sHP_SYSREG.HPCONF.WORD
#define bHP_SYSTEM_HP_PERI_TIMEOUT_THRES sHP_SYSREG.HPCONF.BITS.HP_PERI_TIMEOUT_THRES
#define bHP_PERI_TIMEOUT_INT_CLEAR sHP_SYSREG.HPCONF.BITS.HP_PERI_TIMEOUT_INT_CLEAR
#define bHP_PERI_TIMEOUT_PROTECT_EN sHP_SYSREG.HPCONF.BITS.HP_PERI_TIMEOUT_PROTECT_EN
//28
#define rHP_PERI_TIMEOUT_ADDR_REG
//32
#define rHP_PERI_TIMEOUT_UID sHP_SYSREG.HPUID.WORD
#define bHP_SYSTEM_TIMEOUT_UID_REG sHP_SYSREG.HPUID.BITS.HP_PERI_TIMEOUT_UID



//56
#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x60095038))
#define rHP_SYSTEM_ROM_TABLE_LOCK sHP_SYSREG.LOCKREG.WORD
#define bHP_SYSTEM_TABLE_LOCK sHP_SYSREG.LOCKREG.BITS.TABLE_LOCK
//60
#define rTABLE_REG
//64
#define rCORE_DEBUG_RUNSTALL_CONF_REG sHP_SYSREG.RUNSTALLEN.WORD
#define bHP_SYSTEM_CORE_DEBUG_RUNSTALL_ENABLE sHP_SYSREG.RUNSTALLEN.BITS.DEBUG_RUNSTALL_ENABLE


//03FC ---> 1020
#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x600953FC))
#define rDATE_REG sHP_SYSREG.DATE.WORD
#define bSYSTEM_DATE sHP_SYSREG.DATE.BITS.SYSTEM_DATE



#endif//SYSTEM_REGISTER_H_