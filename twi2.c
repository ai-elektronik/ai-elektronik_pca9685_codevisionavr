void twiinit(void){
//SCL 400kHz
TWSR = 0x00;
TWBR = 0x0C;
//TWI enable
TWCR = (1<<TWEN);
}

void twistart(void){
TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while ((TWCR & (1<<TWINT)) == 0);
}

void twistop(void){
TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void twiwrite(unsigned char data){
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

unsigned char twiread(unsigned char ack)
{
    switch(ack){
    case 1:
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
    break;
    
    case 0:
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
    break;
    }
}

