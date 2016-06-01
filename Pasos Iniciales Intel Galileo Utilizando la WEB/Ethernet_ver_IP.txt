char output[500];
void setup(){
Serial.begin(9600);
}

void loop(){
  
system("ifconfig> log.txt");

FILE *fp;
fp= fopen("log.txt","r");
while(fgets(output,500,fp) != NULL)
Serial.println(output);
fclose(fp);
delay(5000);

}