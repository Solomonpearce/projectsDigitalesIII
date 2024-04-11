/*
 * SYSTEM REGISTER.h
 *
 *  Created on: 10/04/2024
 *      Author: Harold Gómez
 */

#ifndef SYSTEM_REGISTER_H_
#define SYSTEM_REGISTER_H_


//-------HP_SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL_REG (0x0000)-------------------//

enum {
    mHP_SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT = 0x00000001U,
    mHP_SYSTEM_ENABLE_DOWNLOAD_G0CB_ENCRYPT = 0x00000004U,
    mHP_SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT = 0x00000008U,

};

typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_SYSTEM_ENABLE_SPI_MANUAL_ENCRYPT                 :1; // Configures whether or not to enable MSPI XT manual encryption in SPI boot mode.
        uint32_t HP_SYSTEM_ENABLE_DOWNLOAD_G0CB_ENCRYPT              :1; // Configures whether or not to enable MSPI XTS auto decryption in download boot mode.
        uint32_t HP_SYSTEM_ENABLE_DOWNLOAD_MANUAL_ENCRYPT            :1 //Configures whether or not to enable MSPI XTS manual encryption in download boot mode.
        uint32_t                                                     :29; //Reserved
    }BITS;
}__HP_SYSTEM_EXTERNAL_t;



//-----------------HP_SYSTEM_SEC_DPA_CONF_REG (0x0008)--------//

#define mHP_SYSTEM_DPA_LEVEL(X) (X & 0x00000003U) //Macro con reserva de bits en binario y luego a hexa.

enum{
    mHP_SYSTEM_SEC_DPA_CGF_SEL= 0x00000004U,
}; 

enum{
    kHP_SYSTEM_SEC_DPA_OFF, // Security level 0
    kHP_SYSTEM_SEC_DPA_LOW,// Security level 1
    kHP_SYSTEM_SEC_DPA_MIDDLE,//Security level 2
    kHP_SYSTEM_SEC_DPA_HIGH,//Security level 3
};

typedef union{
    uint32_t WORD;      //Access to whole Register
    struct{
        uint32_t SEC_DPA_LEVEL            :2; // Configures whether or not to enable anti-DPA attack. Valid only when HP_SYSTEM_SEC_DPA_CFG_SEL is 0.
        uint32_t SEC_DPA_CFG_SEL          :1; //Configures whether to select HP_SYSTEM_SEC_DPA_LEVEL or EFUSE_SEC_DPA_LEVEL (from eFuse) to control DPA level.
        uint32_t                          :29; //Reserved
    }BITS;
}__HP_SYSTEM_SEC_DPA_t;




//------HP_SYSTEM_ROM_TABLE_LOCK_REG (0x0038)-------//

enum{
    mHP_SYSTEM_TABLE_LOCK = 0x00000001U
};

typedef union {
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t TABLE_LOCK             :1; // Configures whether or not to lock the value contained in HP_SYSTEM_ROM_TABLE.
        uint32_t                        :31 //Reserved.
    }BITS;
    
}__HP_SYSTEM_ROM_TABLE_LOCK_t;


//---------------HP_SYSTEM_ROM_TABLE_REG (0x003C)----------//

typedef union {
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t TABLE_REG             :32; //Software ROM-Table register, whose content can be modified only when HP_SYSTEM_ROM_TABLE_LOCK is 0.
    }BITS;
    
}__HP_SYSTE_ROM_TABLE_REG_t;  



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

}__HP_SYSTEM_CORE_DEBUG_RUNSTALL_CONF_REG_t;



//-------------------------DEFINICION CPU Peripheral Timeout Register-------------------------//

//-------------HP_SYSTEM_CPU_PERI_TIMEOUT_CONF_REG (0x000C)//---------

#define mHP_SYSTEM_CPU_PERI_THRES(X) (X & 0x0000FFFFU)


enum{
    //REVISAR SI ES NECESARIO HAACER CADA UNA DE LAS POSIBLES 16 
}

enum{
    mHP_SYSTEM_CPU_PERI_TIMEOUT_INT_CLEAR = 0x00010000U,
    mHP_SYSTEM_CPU_PERI_TIMEOUT_PROTECT_EN =0x00020000U
};



typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t CPU_TIMEOUT_THRES              :16; // Configures the timeout threshold for bus access for accessing CPU peripheral register in the number of clock cycles of the clock domain.
        uint32_t CPU_TIMEOUT_INT_CLEAR          :1; //Write 1 to clear timeout interrupt.
        uint32_t CPU_TIMEOUT_PROTECT_EN         :1; //Configures whether or not to enable timeout protection for accessing CPU peripheral registers.
    };
};


/*
enum {

}
*/

//HP_SYSTEM_CPU_PERI_TIMEOUT_ADDR_REG (0x0010)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t TIMEOUT_ADDR           :32; // Represents the address information of abnormal access. 

    };
};



/*
enum {

}
*/

//HP_SYSTEM_CPU_PERI_TIMEOUT_UID_REG (0x0014)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t TIMEOUT_UID           :7; //  Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared
        uint32_t                      :25; //Reserved

    };
};


//-------------------------DEFINICION HP Peripheral Timeout Register-------------------------//

/*
enum {

}
*/

//HP_SYSTEM_HP_PERI_TIMEOUT_CONF_REG (0x0018)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_THRES             :16; // Configures the timeout threshold for bus access for accessing HP peripheral register, corresponding to the number of clock cycles of the clock domain.
        uint32_t HP_PERI_TIMEOUT_INT_CLEAR         :1; //configures whether or not to clear timeout interrupt.
        uint32_t HP_PERI_TIMEOUT_PROTECT_EN        :1; //Configures whether or not to enable timeout protection for accessing HP peripheral registers.
        uint32_t                                  :14; //Reserved
    };
};


/*
enum {

}
*/

//Register 16.10. HP_SYSTEM_HP_PERI_TIMEOUT_ADDR_REG (0x001C)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_ADDR          :32; // Represents the address information of abnormal access.
    };
};

/*
enum {

}
*/

// HP_SYSTEM_HP_PERI_TIMEOUT_UID_REG (0x0020)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_PERI_TIMEOUT_UID          :7; // Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared.
        uint32_t                               :25; //Reserved
    };
};


//-------------------------DEFINICION LP Peripheral Timeout Register-------------------------//
/*
enum {

}
*/
//LP_PERI_BUS_TIMEOUT_CONF_REG (0x0010)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_THRES             :16; // Configures the timeout threshold for bus access for accessing LP peripheral register, corresponding to the number of clock cycles of the clock domain.
        uint32_t LP_PERI_TIMEOUT_INT_CLEAR         :1; //configures whether or not to clear timeout interrupt.
        uint32_t LP_PERI_TIMEOUT_PROTECT_EN        :1; //Configures whether or not to enable timeout protection for accessing LP peripheral registers.
        uint32_t                                  :14; //Reserved
    };
};

/*
enum {

}
*/
//LP_PERI_BUS_TIMEOUT_ADDR_REG (0x0014)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_ADDR          :32; // Represents the address information of abnormal access.
    };
};

/*
enum {

}
*/
//LP_PERI_BUS_TIMEOUT_UID_REG (0x0018)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t LP_PERI_TIMEOUT_UID          :7; // Represents the master id[4:0] and master permission[6:5] when trigger timeout. This register will be cleared after the interrupt is cleared.
        uint32_t                               :25; //Reserved
    };
};
//-------------------------DEFINICION Version Register-------------------------//

/*
enum {

}
*/
// HP_SYSTEM_DATE_REG (0x03FC)
typedef union{
    uint32_t WORD; //Access to whole Register
    struct{
        uint32_t HP_SYSTEM_DATE          :28; //Version control register.
        uint32_t                         :4; //Reserved
    };
};


//------DEFINICION------//

