/**
 * @file SYSTEM_REGISTER.h
 * @brief Biblioteca de Hardware para el Micro ESP32-C6
 * 
 * @author Harold Adrián Gómez Gil 
 * @version 1.0
 * @date 13/04/2024
 * @copyright Unlicensed
 * 
 */

#ifndef SYSTEM_REGISTER_H_
#define SYSTEM_REGISTER_H_
#include <stdint.h>


/**
 * @brief Estructura de Unión para representar el registro HP_SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG (0x0000) y además declaración de mascaras para los modulos dentro del registro.
*/
enum {
    mHP_SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT = 0x00000001U, ///< Valor de inicialización para el modulo
    mHP_SYSTEM_ENABLE_DOWNLOAD_G0CB_DECRYPT = 0x00000004U,///< Valor de inicialización para el modulo
    mHP_SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT = 0x00000008U,///< Valor de inicialización para el modulo.
};

typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t SPI_MANUAL_ENCRYPT                 :1; ///< Configures whether or not to enable MSPI XT manual encryption in SPI boot mode.
        uint32_t                                    :1; ///< Reserved
        uint32_t DOWNLOAD_G0CB_DECRYPT              :1; ///< Configures whether or not to enable MSPI XTS auto decryption in download boot mode.
        uint32_t DOWNLOAD_MANUAL_ENCRYPT            :1; ///< Configures whether or not to enable MSPI XTS manual encryption in download boot mode.
        uint32_t                                    :28; ///< Reserved
    }BITS;
}__HP_SYSTEM_EXTERNAL_t;



/**
 * @brief Estructura de Unión para representar el registro HP_SYSTEM_SEC_DPA_CONF_REG (0x0008). 
 * @details Se presenta además la mascara respectiva para definir los valores de las constantes presentes en el modulo y cada una de las constantes presentes. 
*/
#define mHP_SYSTEM_DPA_LEVEL 0x00000003U ///< Valor de inicialización para el modúlo HP_SYSTEM_DEC_DPA_LEVEL

enum{
    kSEC_DPA_OFF, ///< Security level 0
    kSEC_DPA_LOW,///< Security level 1
    kSEC_DPA_MIDDLE,///< Security level 2
    kSEC_DPA_HIGH,///< Security level 3    
};

enum{
    mHP_SYSTEM_SEC_DPA_CGF_SEL= 0x00000004U, ///< mascara para el modulo.
}; 

typedef union{
    uint32_t WORD;      ///< Access to whole Register
    struct{
        uint32_t SEC_DPA_LEVEL            :2; ///< Configures whether or not to enable anti-DPA attack. Valid only when HP_SYSTEM_SEC_DPA_CFG_SEL is 0.
        uint32_t SEC_DPA_CFG_SEL          :1; ///< Configures whether to select HP_SYSTEM_SEC_DPA_LEVEL or EFUSE_SEC_DPA_LEVEL (from eFuse) to control DPA level.
        uint32_t                          :29; ///< Reserved
    }BITS;
}__SEC_DPA_CONF_t;



/**
 * @brief Estructura de Unión para Representar el registro HP_SYSTEM_ROM_TABLE_LOCK_REG (0x0038)
*/
enum{
    mHP_SYSTEM_TABLE_LOCK = 0x00000001U ///< Valor de inicialización para el modulo.
};

typedef union {
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t TABLE_LOCK             :1; ///< Configures whether or not to lock the value contained in HP_SYSTEM_ROM_TABLE.
        uint32_t                        :31; ///< Reserved.
    }BITS;
    
}__HP_SYSTEM_ROM_TABLE_LOCK_t;

/**
 * @brief Declaración unica del registro HP_SYSTEM_ROM_TABLE_REG (0x003C)
*/
    uint32_t TABLE_REG; ///< Software ROM-Table register, whose content can be modified only when HP_SYSTEM_ROM_TABLE_LOCK is 0.

/**
 * @brief Estructura de union para representar el registro HP_SYSTEM_CORE_DEBUG_RUNSTALL_CONF_REG (0x0040)
*/

enum{
    mHP_SYSTEM_CORE_DEBUG_RUNSTALL_ENABLE = 0x00000001U///<  Valor de inicialización del modulo
};

typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t DEBUG_RUNSTALL_ENABLE            :1; ///< Configures whether or not to enable debug RunStall functionality between HP CPU and LP CPU.
        uint32_t                                  :31; ///< Reserved.
    }BITS;

}__CORE_DEBUG_RUNSTALL_CONF_REG_t;



///////////-------------------------------------------------DEFINICION CPU Peripheral Timeout Register-------------------------////////////





/**
 * @brief Estructura de Unión para el registro HP_SYSTEM_CPU_PERI_TIMEOUT_CONF_REG (0x000C)
 * @details Contiene Además la definición de mascaras  y valores de inicialización de cada modulo en el registro.
*/


#define mHP_SYSTEM_CPU_PERI_THRES 0x0000FFFFU///< Asignación de 16 bits al modulo.
enum{
    mHP_SYSTEM_CPU_PERI_TIMEOUT_INT_CLEAR = 0x00000001U<<16, ///< Mascara con respectiva asignación al modulo.
    mHP_SYSTEM_CPU_PERI_TIMEOUT_PROTECT_EN =0x00000001U<<17///< Mascara con respectiva asignación al modulo
};

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t CPU_PERI_TIMEOUT_THRES              :16; ///< Configures the timeout threshold for bus access for accessing CPU peripheral register in the number of clock cycles of the clock domain.
        uint32_t CPU_PERI_TIMEOUT_INT_CLEAR          :1; ///< Write 1 to clear timeout interrupt.
        uint32_t CPU_PERI_TIMEOUT_PROTECT_EN         :1; ///< Configures whether or not to enable timeout protection for accessing CPU peripheral registers.
    }BITS;
}__PERI_TIMEOUT_CONF_REG_t;


/**
 * @brief Estructura de Unión para el registro HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG (0x0010).
 * @details Considerando que se comparte la misma posición de memoria con otro registro, se usa la estructura de unión y se añade una mascara al modulo, que corresponde al primer registro con la misma dirección, posterior a ello, se define también la estructura en donde se hace la asignación al otro modulo y además se nombra el miembro de la estructura de BITS como BITSA para evitar confusiones.
*/
#define mHP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG 0xFFFFFFFFU
enum{
    mHP_SYSTEM_CPU_PERI_TIMEOUT_ADDR = 0xFFFFFFFFU
};
typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t TIMEOUT_ADDR              :32; ///< Represents the address information of abnormal access. 
    }BITSA;
}__HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG_t;


/**
 * @brief Estructura de unión para el registro HP_SYSTEM_CPU_PERI_TIMEOUT_UID_REG (0x0014)
*/
#define mHP_SYSTEM_CPU_PERI_TIMEOUT_UID 0x0000007FU ///< Asignación de bits para el modulo
typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t TIMEOUT_UID           :7; ///< Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared
        uint32_t                      :25; ///< Reserved

    }BITS;
}__PERI_TIMEOUT_UID_t;


//////////////-----------------------------------------DEFINICION HP Peripheral Timeout Register-------------------------///////////////////


/**
 * @brief Estructura de union para el registro HP_SYSTEM_HP_PERI_TIMEOUT_CONF_REG (0x0018)
*/
#define mHP_SYSTEM_HP_PERI_TIMEOUT_THRES 0x0000FFFFU ///< Asignación de bits por defecto para el modulo

enum {
    mHP_PERI_TIMEOUT_INT_CLEAR = 0x00000001U<<16, ///< Mascara de asignación del modulo
    mHP_PERI_TIMEOUT_PROTECT_EN = 0x00000001U<<17///< Mascara de asignación del modulo

};
typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_THRES             :16; ///< Configures the timeout threshold for bus access for accessing HP peripheral register, corresponding to the number of clock cycles of the clock domain.
        uint32_t HP_PERI_TIMEOUT_INT_CLEAR         :1; ///< configures whether or not to clear timeout interrupt.
        uint32_t HP_PERI_TIMEOUT_PROTECT_EN        :1; ///< Configures whether or not to enable timeout protection for accessing HP peripheral registers.
        uint32_t                                  :14; ///< Reserved
    }BITS;
}__HP_TIMEOUT_CONF_REG_t;



/**
*@brief Declaración unica del registro HP_SYSTEM_HP_PERI_TIMEOUT_ADDR_REG (0x001C)
*/
    uint32_t HP_PERI_TIMEOUT_ADDR_REG; // Represents the address information of abnormal access.



/**
 * @brief Estructura de unión para el registro HP_SYSTEM_HP_PERI_TIMEOUT_UID_REG (0x0020)
*/

#define mHP_SYSTEM_TIMEOUT_UID_REG 0x0000007FU ///< Asignación de bits por defecto para el modulo

typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_UID          :7; ///< Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared.
        uint32_t                               :25; ///< Reserved
    }BITS;
}__HP_PERI_TIMEOUT_UID_t;


////////////-----------------------------------------------DEFINICION LP Peripheral Timeout Register-------------------------------//////////



/**
 * @brief Estructura de Unión para el registro LP_PERI_BUS_TIMEOUT_CONF_REG (0x0010)
 * @details Este registro comparte dirección de memoria 0x0010 con el registro HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG.
*/
#define mLP_PERI_BUS_TIMEOUT_THRES 0x0000FFFFU ///< Asignación de bits por defecto del modulo
enum{
    mBUS_TIME_OUT_INT_CLEAR = 0x00000001U<<16,///< Asignación de bits por defecto para el modulo mediante mascara
    mBUS_TIME_OUT_PROTECT_EN = 0x00000001U<<17///< Asignación de bits por defecto para el modulo mediante mascara
};

typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_THRES             :16; ///< Configures the timeout threshold for bus access for accessing LP peripheral register, corresponding to the number of clock cycles of the clock domain.
        uint32_t LP_PERI_TIMEOUT_INT_CLEAR         :1; ///< configures whether or not to clear timeout interrupt.
        uint32_t LP_PERI_TIMEOUT_PROTECT_EN        :1; ///< Configures whether or not to enable timeout protection for accessing LP peripheral registers.
        uint32_t                                  :14; ///< Reserved
    }BITS;
}__BUS_TIMEOUT_CONF_REG_t;


/**
 * @brief Estructura de Unión para el registro LP_PERI_BUS_TIMEOUT_ADDR_REG (0x0014)
 * @details Este registro comparte dirección de memoria 0x0014 con el registro HP_SYSTEM_CPU_PERI_TIMEOUT_UID_REG es por ello que si bien se trata de un registro con asignación de la totalidad de bits, se debe hacer uso de la de estructura de unión, para definir así los campos de BITS , con el nombre BITSA evitando así problemas de acceso.
*/

uint32_t LP_PERI_TIMEOUT_ADDR;
#define mLP_PERI_BUS_TIMEOUT_ADDR_REG 0xFFFFFFFFU ///< Asignación de bits por defecto para el modulo
enum{
    mLP_PERI_BUS_TIMEOUT_ADDR = 0xFFFFFFFFU///< mascara de asignación para el modulo
};
typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t LP_PERI_BUS_TIMEOUT_ADDR              :32; ///< Represents the address information of abnormal access. 
    }BITSA;
}__LP_PERI_BUS_TIMEOUT_ADDR_REG_t;


/**
 * @brief Estructura de Unión para el registro LP_PERI_BUS_TIMEOUT_UID_REG (0x0018)
 * @details Este registro comparte dirección de memoria 0x0018 con el registro HP_SYSTEM_HP_PERI_TIMEOUT_CONF_REG, es por ello que se define entonces para acceder a la estructura del modulo no con el nombre "BITS" sinó "BITSA"
*/
#define mLP_PERI_BUS_TIMEOUT_UID 0x0000007FU ///< Asignación de bits del modulo 
typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_UID          :7; ///< Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared.
        uint32_t                               :25; ///< Reserved
    }BITSA;
}__TIME_OUT_UID_REG_t;



////////////-------------------------------------DEFINICION Version Register-------------------------/////////////////////////////

/**
 * @brief Estructura de unión para el registro HP_SYSTEM_DATE_REG (0x03FC)
*/
#define mSYSTEM_DATE 0x0FFFFFFFU ///< Asignación de bits del modulo
typedef union{
    uint32_t WORD; ///< Access to whole Register
    struct{
        uint32_t SYSTEM_DATE          :28; ///< Version control register.
        uint32_t                        :4; ///< Reserved
    }BITS;
}__DATE_REG_t;


//------DEFINICION------//
typedef struct {
    volatile __HP_SYSTEM_EXTERNAL_t EXTERNAL; ///< Registro en Offset 0x0000
    volatile __SEC_DPA_CONF_t CONFREG; ///< Registro en Offset 0x0008
    volatile __HP_SYSTEM_ROM_TABLE_LOCK_t LOCKREG;///< Registro en Offset 0x0038
    volatile __CORE_DEBUG_RUNSTALL_CONF_REG_t RUNSTALLEN;///< Registro en Offset 0x0040
    volatile __PERI_TIMEOUT_CONF_REG_t PERICONFREG; ///< Registro en Offset 0x000C
    volatile __HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG_t PERITIMEADD;///< Registro en Offset 0x0010
    volatile __PERI_TIMEOUT_UID_t PERIUIDREG;///< Registro en Offset 0x0014
    volatile __HP_TIMEOUT_CONF_REG_t HPCONF; ///< Registro en Offset 0x0018
    volatile __HP_PERI_TIMEOUT_UID_t HPUID;///< Registro en Offset 0x0020
    volatile __BUS_TIMEOUT_CONF_REG_t BUSCONF; ///< Registro en Offset 0x0010
    volatile __LP_PERI_BUS_TIMEOUT_ADDR_REG_t BUSTIMEADD; ///< Registro en Offset 0x0014
    volatile __TIME_OUT_UID_REG_t BUSUID;///< Registro en Offset 0x0018
    volatile __DATE_REG_t DATE;///< Registro en Offset 0x03FC
}__HP_SYSREG_t;





/**
 * @brief Macros de Acceso a cada una de las instancias de presentes en los registros
 * @details Proporciona acceso a todos los registros a través del puntero __HP_SYSREG_t
*/
#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x60095000))///< Macro de acceso a la instancia del registro
/**
 * @brief Instancias de Acceso para el modulo HP_SYSTEM_EXTERNAL
*/
#define rHP_SYSTEM_EXTERNAL sHP_SYSREG.EXTERNAL.WORD
#define bHP_SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT sHP_SYSREG.EXTERNAL.BITS.SPI_MANUAL_ENCRYPT
#define bHP_SYSTEM_ENABLE_DOWNLOAD_G0CB_DECRYPT sHP_SYSREG.EXTERNAL.BITS.DOWNLOAD_G0CB_DECRYPT
#define bHP_SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT sHP_SYSREG.EXTERNAL.BITS.DOWNLOAD_MANUAL_ENCRYPT


/**
 * @brief Instancias de Acceso para el modulo SEC_DPA_CONF
 * @details Se asigna un macro para acceder a la instancia del modulo, debido a que no es un modulo consecutivo.
*/
#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x60095008)) ///< Macro de Acceso al modulo

#define rSEC_DPA_CONF sHP_SYSREG.CONFREG.WORD
#define bHP_SYSTEM_DPA_LEVEL sHP_SYSREG.CONFREG.BITS.SEC_DPA_LEVEL
#define bHP_HP_SYSTEM_SEC_DPA_CGF_SEL sHPSYSREG.CONFREG.BITS.SEC_DPA_CFG_SEL

/**
 * @brief Instancias de Acceso para  PERI_TIMEOUT_CONF_REG
*/
#define rPERI_TIMEOUT_CONF_REG sHP_SYSREG.PERICONFREG.WORD
#define bHP_SYSTEM_CPU_PERI_THRES sHP_SYSREG.PERICONFREG.BITS.CPU_PERI_TIMEOUT_THRES
#define bHP_SYSTEM_CPU_PERI_TIMEOUT_INT_CLEAR sHP_SYSREG.PERICONFREG.BITS.CPU_PERI_TIMEOUT_INT_CLEAR
#define bHP_SYSTEM_CPU_PERI_TIMEOUT_PROTECT_EN sHP_SYSREG.PERICONFREG.BITS.CPU_PERI_TIMEOUT_PROTECT_EN
/**
 * @brief Instancias de Acceso para HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR ó BUS_TIMEOUT_CONF_REG
 * @details En esta instancia se tiene la misma dirección de memoria para dos registros, por ello se tiene el indicador de la estructura como BITSA y BITS, esto para evitar conflictos con las direcciones. 
*/
#define rHP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG sHP_SYSREG.PERITIMEADD.WORD
#define bBUS_TIME_OUT_INT_CLEAR sHP_SYSREG.PERITIMEADD.BITSA.TIMEOUT_ADDR

#define rBUS_TIMEOUT_CONF_REG sHP_SYSREG.BUSCONF.WORD
#define bLP_PERI_BUS_TIMEOUT_THRES sHP_SYSREG.BUSCONF.BITS.LP_PERI_TIMEOUT_THRES
/**
 * @brief Instancias de Acceso para PERI_TIMEOUT_UID ó LP_PERI_BUS_TIMEOUT_ADDR_REG
 * @details En esta instancia se tiene la misma dirección de memoria para dos registros, por ello se tiene el indicador de la estructura como BITSA y BITS, esto para evitar conflictos con las direcciones. 
*/
#define rPERI_TIMEOUT_UID sHP_SYSREG.PERIUIDREG.WORD
#define bHP_SYSTEM_CPU_PERI_TIMEOUT_UID sHP_SYSREG.PERIUIDREG.BITS.TIMEOUT_UID

#define rLP_PERI_BUS_TIMEOUT_ADDR_REG sHP_SYSREG.BUSTIMEADD.WORD
#define bLP_PERI_BUS_TIMEOUT_ADDR sHP_SYSREG.BUSTIMEADD.BITSA.LP_PERI_BUS_TIMEOUT_ADDR

/**
 * @brief Instancias de acceso para HP_TIMEOUT_CONF_REG ó TIME_OUT_UID_REG
 * @details En esta instancia se tiene la misma dirección de memoria para dos registros, por ello se tiene el indicador de la estructura como BITSA y BITS, esto para evitar conflictos con las direcciones. 
*/
#define rHP_TIMEOUT_CONF_REG sHP_SYSREG.HPCONF.WORD
#define bHP_SYSTEM_HP_PERI_TIMEOUT_THRES sHP_SYSREG.HPCONF.BITS.HP_PERI_TIMEOUT_THRES
#define bHP_PERI_TIMEOUT_INT_CLEAR sHP_SYSREG.HPCONF.BITS.HP_PERI_TIMEOUT_INT_CLEAR
#define bHP_PERI_TIMEOUT_PROTECT_EN sHP_SYSREG.HPCONF.BITS.HP_PERI_TIMEOUT_PROTECT_EN

#define rTIME_OUT_UID_REG sHP_SYSREG.BUSUID.WORD
#define bLP_PERI_BUS_TIMEOUT_UID sHP_SYSREG.BUSUID.BITSA.LP_PERI_TIMEOUT_UID

/**
 * @brief Instancia de acceso para HP_PERI_TIMEOUT_ADDR_REG
*/
#define rHP_PERI_TIMEOUT_ADDR_REG
/**
 * @brief Instancia de acceso para HP_PERI_TIMEOUT_UID
*/
#define rHP_PERI_TIMEOUT_UID sHP_SYSREG.HPUID.WORD
#define bHP_SYSTEM_TIMEOUT_UID_REG sHP_SYSREG.HPUID.BITS.HP_PERI_TIMEOUT_UID

/**
 * @brief Macro de acceso a partir del Offset del último registro consecutivo 
*/
#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x60095038))
/**
 * @brief Instancia de acceso para HP_SYSTEM_ROM_TABLE_LOCK
*/
#define rHP_SYSTEM_ROM_TABLE_LOCK sHP_SYSREG.LOCKREG.WORD
#define bHP_SYSTEM_TABLE_LOCK sHP_SYSREG.LOCKREG.BITS.TABLE_LOCK
/**
 * @brief Instancia de acceso para TABLE_REG
*/
#define rTABLE_REG
/**
 * @brief Instancia de acceso para CORE_DEBUG_RUNSTALL_CONF_REG
*/
#define rCORE_DEBUG_RUNSTALL_CONF_REG sHP_SYSREG.RUNSTALLEN.WORD
#define bHP_SYSTEM_CORE_DEBUG_RUNSTALL_ENABLE sHP_SYSREG.RUNSTALLEN.BITS.DEBUG_RUNSTALL_ENABLE

/**
 * @brief Instancia de acceso para DATE_REG
 * @details Se declara además un macro para la ultima dirección en memoria correspiente al offset del registro en cuestión 
*/
#define sHP_SYSREG (*(__HP_SYSREG_t *)(0x600953FC))
#define rDATE_REG sHP_SYSREG.DATE.WORD
#define bSYSTEM_DATE sHP_SYSREG.DATE.BITS.SYSTEM_DATE

#endif///< SYSTEM_REGISTER_H_