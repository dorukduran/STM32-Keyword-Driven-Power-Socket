#include "my_main.h"
#include <deque>
#include <cmath>
#include "kws.h"
#include "mfcc.h"



#define ON 0b111111000010
#define OFF 0b111111000001
int OFFSET = 8000;
const int I2S_BUF_SIZE = 1000;
uint16_t inputBuffer1[I2S_BUF_SIZE*2];
int32_t mergedFrame[I2S_BUF_SIZE/4];
bool isRC = false;
TIM_HandleTypeDef* htim4__;
int32_t ISA[16000];
int32_t RingBuffer[4000];
volatile bool datenVerarbeiten = false;
int RingBufferSize = 4000;
int RingBufferIndex=0;
int iZaehler=0;
int AudioInput=0;
int rcStTm;
int noise=12000;
#define MFCC_IN_SIZE 800
#define MFCC_STEP_SIZE 320
#define MFCC_OUT_SIZE 10
MFCC* mfcc = new MFCC(MFCC_OUT_SIZE, MFCC_IN_SIZE, 2);
KWS *kws=new KWS();
LCD_HandleTypeDef* lcddev;
uint16_t timer_val;
I2C_HandleTypeDef* _hi2c2;
void delay350Microseconds(int i);
void sendSequence(uint16_t bitSequence);
void transmit(int nHighPulses, int nLowPulses);
void LauteZeig();
void MFCCuebergeben(char*);
void initializeLCD();
void displayLCD(const char*);
std::string lastCommand = "";

std::deque<char*> commandHistory;

// Fügt einen neuen Befehl zur Befehlshistorie hinzu
void addCommandToHistory(char* command) {
    const size_t maxHistorySize = 20; // Maximale Anzahl der zu speichernden Befehle
    if (commandHistory.size() >= maxHistorySize) {
        // Wenn die Historie voll ist, den ältesten Befehl entfernen
        commandHistory.pop_front();
    }
    // Neuen Befehl hinzufügen
    commandHistory.push_back(command);
}

// Überprüft den vorherigen Befehl
bool checkPreviousCommand(char* command) {
    if (!commandHistory.empty()) {
        // Überprüft das letzte Element der Historie
        return strcmp(commandHistory.back(), command)==0;
    }
    return false; // Wenn die Historie leer ist, false zurückgeben
}

void delay350Microseconds(int i)
{
	//TIM_HandleTypeDef htim4;
	uint16_t timer_val;
	uint16_t tim_diff=350*i;
	HAL_TIM_Base_Start(htim4__);
	timer_val=__HAL_TIM_GET_COUNTER(htim4__);
	while( __HAL_TIM_GET_COUNTER(htim4__)-timer_val<tim_diff)
	{

	}
	//HAL_TIM_Base_Stop(&htim4);

}

void transmit(int nHighPulses, int nLowPulses)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	delay350Microseconds(nHighPulses);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	delay350Microseconds(nLowPulses);
}

void sendSequence(uint16_t bitSequence)
{
	int t=0;
	int i=0;
	for(t=0 ; t<10;t++)
	{
		for( i = 0; i < 12; i++)
		{
			transmit(1, 3);
			//shift
			if((bitSequence << i) & (1 << 11))
			{
				transmit(1, 3);// 1
			}
			else
			{
				transmit(3, 1);// 0
			}
		}
		transmit(1,31);
	}

}

void initializeLCD() {
	LCD_Clear(lcddev);
	LCD_SetCursor(lcddev, 0, 0);
    LCD_Print(lcddev, "Test");
}

void displayLCD(const char* message) {
	LCD_Clear(lcddev);
    LCD_Print(lcddev, message);
}

void setTimer(int minutes) {
    uint32_t start_time = __HAL_TIM_GET_COUNTER(htim4__);
    uint32_t end_time = start_time + minutes * 60 * 1000000;

    sendSequence(ON);

    while (__HAL_TIM_GET_COUNTER(htim4__) < end_time) {
        HAL_Delay(1000);
    }

    sendSequence(OFF);
}


void turnOffLEDArray() {
    GPIO_TypeDef* LED_PORTS[] = {GPIOG, GPIOG, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOF, GPIOB};
    uint16_t LED_PINS[] = {GPIO_PIN_14, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_7, GPIO_PIN_10, GPIO_PIN_12, GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_15, GPIO_PIN_11};

    for (int i = 0; i < 10; i++) {
        HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_RESET);
    }
}

void Konvertierung()
{
	MFCC* mfcc = new MFCC(MFCC_OUT_SIZE, MFCC_IN_SIZE, 2);
	KWS * kws= new KWS();
	float mfccInputFrame[MFCC_IN_SIZE]; // input frame of mfcc
	q7_t mfccOutTmp[MFCC_OUT_SIZE]; // result of mfcc
	//float mfccOut[MFCC_OUT_SIZE]; // result after typecast

	//Feature extraction
	printf("Feature extraction started\r\n");
	int feature_counter = 0;
	for (int i = 0; i < 16000-MFCC_STEP_SIZE; i+=MFCC_STEP_SIZE,feature_counter++)
	{
		for (int j = 0; j < MFCC_IN_SIZE; j++)
		{
			if (i+j >= 16000)
				mfccInputFrame[j] = 0;
			else
			{
				mfccInputFrame[j] = (float) ISA[i+j];
				//printf("%f, ", mfccInputFrame[j]);
			}
		}
		mfcc->mfcc_compute(mfccInputFrame, mfccOutTmp);
		for (int k = 0; k < MFCC_OUT_SIZE; k++)
		{
			kws->mMFCC[feature_counter][k] = (ai_float) mfccOutTmp[k];
		}
	}
	printf("Feature extraction ended\r\n");
	//typcast
	/*for (int m = 0; m < MFCC_OUT_SIZE; m++)
	{
		mfccOut[m]=float(mfccOutTmp[m]);
	}*/
	float index2=kws->runInference();

	std::string result=kws->indexToWord(index2);





	char *str = (char*)result.data();
	printf("%s\n",str);
	delete kws;
	delete mfcc;
	MFCCuebergeben(str);


}
void Audio1Sec()
{

      int alpha = 0.1;  // Faktor zur Anpassung des Schwellwerts
	  int loudSoundCounter = 0;
	  const int LOUD_SOUND_DURATION = 5;
	 for (int i = 0; i < I2S_BUF_SIZE/4; i++)
	 {
		 OFFSET= alpha * abs(mergedFrame[i]) + (1 - alpha) * OFFSET;
		 //printf("Offset: %d Frame: %d\n", OFFSET, mergedFrame[i]);
		  // Überprüfen, ob das Signal lauter als der Schwellwert ist
			if (abs(mergedFrame[i]) > OFFSET)
			{
				loudSoundCounter++;
			} else
			{
				loudSoundCounter = 0;  // Zurücksetzen, wenn das Geräusch nicht mehr laut ist
			}
				 //// Filtern von Geräuschen unter dem Schwellwert
		   if(abs(mergedFrame[i])>noise)
		   {
			   continue;//// Überspringen der aktuellen Iteration
		   }

			   //ein Teil des Audiosignal vor der Überschreitung des Schwellwert
			   RingBuffer[RingBufferIndex] = mergedFrame[i];
			   RingBufferIndex = (RingBufferIndex + 1) % RingBufferSize;
		 if (abs(mergedFrame[i])>OFFSET&& !isRC&&loudSoundCounter >= LOUD_SOUND_DURATION)
		 {
			 isRC= true;

			 rcStTm = HAL_GetTick();
			 printf("Aufnahme beginnt\n");
			 int copyIndex = RingBufferIndex;
			 for(int k=0;k<RingBufferSize;k++)
			 {
				 ISA[iZaehler++] = RingBuffer[copyIndex];
				 copyIndex = (copyIndex + 1) % RingBufferSize;
			 }

		 }


		 if(isRC)
        {

 				ISA[iZaehler++] = mergedFrame[i];
 				if(iZaehler==16000)
 				{
 					iZaehler=0;
 					Konvertierung();
 					isRC = false;
 					printf("Aufnahme beendet. Dauer: %lu ms\n", HAL_GetTick() - rcStTm);
 				break;
 				}



        }
	 }
}


void Control_LEDs(int32_t numberOfLEDs) {

    GPIO_TypeDef* LED_PORTS[] = {GPIOG, GPIOG, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOF, GPIOB};
    uint16_t LED_PINS[] = {GPIO_PIN_14, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_7, GPIO_PIN_10, GPIO_PIN_12, GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_15, GPIO_PIN_11};


    for (int i = 0; i < 10; i++) {
        HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_RESET);
    }

    for (int i = 0; i < numberOfLEDs; i++) {
        if (i < 10)
        {
            HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_SET);
        }
    }
}


void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s2 )
{
	if(!datenVerarbeiten) {

	    }
	else
	{
	for (int i = 0, j = 0; i < I2S_BUF_SIZE ; i += 4, j++)
			{
				// Zm
				int32_t mv = ((int32_t)inputBuffer1[i] << 16) | inputBuffer1[i + 1];
				mv= ((int32_t)mv>>14);
				// Sp
				mergedFrame[j] = mv;
				//printf("%d\n",mv);
			}
	Audio1Sec();
	}


}

void TimerCallback()
{
    datenVerarbeiten = true;
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s2)
{
	if(!datenVerarbeiten) {

	    }
	else
	{
	for (int i =I2S_BUF_SIZE , j = 0; i < I2S_BUF_SIZE*2 ; i += 4, j++)
			{
				// Zm
				int32_t mv = ((int32_t)inputBuffer1[i] << 16) | inputBuffer1[i + 1];
				mv= ((int32_t)mv>>14);
				// Sp
				mergedFrame[j] = mv;
				//printf("%d\n",mv);
			}
	Audio1Sec();
	}
}


void LauteZeig()
{
	//static bool seStat = false;

    for (int i = 0; i < I2S_BUF_SIZE/4; i++)
    {
    	HAL_Delay(3000);
     	int al=(mergedFrame[i]/1000)-5;
        Control_LEDs(al); // 音量展示
       /* if(mergedFrame[i]>OFFSET)
        {
        	//int al=(mergedFrame[i]/1000)-4;
        	//Control_LEDs(al); // 音量展示
        	   if(seStat==false )
        	   {
        		   // No used
        		   sendSequence(ON);
        		  seStat = !seStat;
        	   }
        	   else
        	   {
        		   sendSequence(OFF);
        		  seStat = !seStat;
        	   }
        }
        else
        {
        	//Control_LEDs(1);
        }
    }*/
    }
}

int mittelwert()
{
	  int volume = 0;

	    // 遍历
	    for (int i = 0; i < I2S_BUF_SIZE/4; i++) {
	        volume += abs(mergedFrame[i]);  // 注意绝对值
	    }
	    volume /=(I2S_BUF_SIZE/4) ;  // 平均值
	    return volume;


}
void MFCCuebergeben(char* result) {
    //Konvertierung();



	if(!commandHistory.empty()) printf("Last Cmd %s\n", commandHistory.back());
    // Zustand des Buttons überprüfen (Button Backup)
    int buttonPressCount = 0;
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
        // Taste wurde gedrückt, Zähler erhöhen
        buttonPressCount++;
        // Warten, bis die Taste losgelassen wird
        while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
        HAL_Delay(250); // Kurze Verzögerung für Entprellung
        // Überprüfen, ob die Taste erneut gedrückt und losgelassen wird
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
            buttonPressCount++;
            // Warten, bis die Taste losgelassen wird
            while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
        }
    }
    	if (strcmp(result, "ON")==0) {
        // Steckdose wird eingeschaltet und Modi auf dem LCD angezeigt
        sendSequence(ON);
        //displayLCD("Socket ON");
        printf("\nSocket ON\n1. Timer Mode\n2. Night Mode");
    	}
        if ((strcmp(result, "ONE")==0 || buttonPressCount == 1) && lastCommand==("ON")) {
            // Timer-Modus wird aktiviert
            //displayLCD("1-15m 2-60m 3-d");
            printf("\n1. 15 minuten\n2. 60 minuten\n3. Dauerhaft");
        } else if ((strcmp(result , "TWO")==0 || buttonPressCount == 2) && lastCommand==("ON")) {
            // Nachtmodus wird aktiviert
            turnOffLEDArray();
        } else {
            // Bei unbekanntem oder unerwartetem Befehl
            //displayLCD("unbekannter Befehl");
            //printf("unbekannter Befehl\n");
        }

        if (strcmp(result, "OFF")==0) {
        //displayLCD("Sicher? 1.Y 2.N");
        printf("\nSind Sie sicher?\n1.YES\n2.NO");
        }
        if ((strcmp(result, "YES")==0 || buttonPressCount == 1) && lastCommand==("OFF"))  {
            // Steckdose wird ausgeschaltet
            sendSequence(OFF);
        } else if ((strcmp(result, "NO")==0 || buttonPressCount == 2)&& lastCommand==("OFF")) {
            // Bei "NO", keine Aktion
        } else {
            // Bei unbekanntem oder unerwartetem Befehl
            //displayLCD("unbekannter Befehl");
            //printf("unbekannter Befehl\n");
        }

        if ((strcmp(result, "ONE")==0 || buttonPressCount == 1) && lastCommand==("ONE")) {
            // Timer auf 15 Minuten gesetzt
            setTimer(15);
            //displayLCD("15 Minuten ");
            printf("\nTimer für 15 Minuten eingestellt");
        } else if ((strcmp(result, "TWO")==0 || buttonPressCount == 2) && lastCommand==("ONE")) {
            // Timer auf 1 Stunde gesetzt
            setTimer(60);
            //displayLCD("1 Stunde");
            printf("\nTimer für 1 Stunde eingestellt");
        } else if ((strcmp(result,"THREE")==0 || buttonPressCount == 3) && lastCommand==("ONE")) {
            // Steckdose bleibt an
            //displayLCD("Dauerhaft");
            printf("\nSteckdose bleibt eingeschaltet");
        } else {
            // Timer-Modus abgebrochen
            //displayLCD("Timer beendet");
            printf("\nTimer-Modus abgebrochen");
        }
        addCommandToHistory(result);
        lastCommand = result;
    }



void my_main(I2S_HandleTypeDef* hi2s2,TIM_HandleTypeDef* htim4_,I2C_HandleTypeDef* __hi2c2)
{
	HAL_I2S_Receive_DMA(hi2s2, &inputBuffer1[0], I2S_BUF_SIZE);

	int t=HAL_GetTick();
	while(HAL_GetTick()-t<2000)
	{

	}
	printf("2 Sekunde vorbei\n");
	TimerCallback();
	htim4__=htim4_;
	HAL_TIM_Base_Start(htim4__);
	_hi2c2=__hi2c2;
	lcddev = new LCD_HandleTypeDef();
	lcddev->i2c_addr = LCD_DEFAULT_ADDR;
	lcddev->backlight_enable = 1;
	lcddev->i2c = __hi2c2;
	LCD_Begin(lcddev);
	initializeLCD();
	//sendSequence(ON);



	while(1)
	{

		/*HAL_GPIO_TogglePin(LD1_GPIO_Port,LD1_Pin);
		HAL_Delay(1000);*/
		//Control_LEDs(5);
		//HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);

		//sendSequence(0b111111000010);
		//sendSequence(ON);
		//I2S_HandleTypeDef hi2s2;


		/*int volume;
		volume=mittelwert();


		//for(int loop = 0; loop < 1; loop++)
			printf("%d ", volume);*/
		LauteZeig();




	}


}



