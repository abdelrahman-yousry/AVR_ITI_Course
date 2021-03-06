#define SET_BIT(Reg,Bit)          (Reg)|=(1<<(Bit))
#define CLR_BIT(Reg,Bit)          Reg&=~(1<<Bit)
#define GET_BIT(Reg,Bit)          ((Reg>>Bit)&1)
#define RSHIFT_REG(Reg,No)        Reg=Reg<<(No)
#define LSHIFT_REG(Reg,No)        Reg=Reg>>(No)
#define CRSHIFT_REG(Reg,No)       Reg=((Reg)<<(No))|((Reg)>>((sizeof(Reg)*8)-(No)))
#define CLSHIFT_REG(Reg,No)       Reg=((Reg)>>(No))|((Reg)<<((sizeof(Reg)*8)-(No)))
#define ASSIGN_REG(Reg,Value)     Reg=Value
#define SET_REG(Reg)              Reg=(~0)
#define CLR_REG(Reg)              Reg =0
#define TGL_BIT(Reg,Bit)          Reg^=(1<<Bit)
#define TGL_REG(Reg)              Reg^=~(0)
#define SET_H_NIB(Reg)            Reg|=F0   
#define SET_L_NIB(Reg)            Reg|=0F   
#define CLR_H_NIB(Reg)            Reg&=0F   
#define CLR_L_NIB(Reg)            Reg&=F0 
#define GET_H_NIB(Reg)            Reg|=F0 
#define GET_L_NIB(Reg)            Reg|=0F   
#define ASSIGN_H_NIB(Reg,Value)   Reg|=(Value<<4)
#define ASSIGN_L_NIB(Reg,Value)   Reg|=(Value)
#define TGL_H_NIB(Reg)            Reg^=F0
#define TGL_L_NIB(Reg)            Reg^=0F
#define SWAP_NIP(Reg)             Reg=(Reg<<4)|(Reg>>4)


