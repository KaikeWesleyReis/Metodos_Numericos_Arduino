// Traduzindo codigos de Matlab para o Arduino

//Exemplo de Resolução de um Sistema de EDO de 4ª Ordem

/*
Exemplo Proposto:
  
Resolver o SEDO abaixo:
      
     dydx = (- 10*z + 10*r - 5*y + 5*w + 15)/250; 
     dzdx = y;
     dwdx = (10*z - 18*r + 5*y - 5*w  - 14.2)/10;
     drdx = w;

Considerar: 
     Condicoes iniciais: y0 = z0 = w0 = r0 = 0 
     x0= 0 e xf= 10;
*/

void setup() {
  Serial.begin(9600);
}

float f1(float x,float y,float z,float w,float r){  //Funcao que calcula a funcao de interesse
  return ((- 10*z + 10*r - 5*y + 5*w + 15)/250);
}

float f2(float x,float y,float z,float w,float r){  //Funcao que calcula as derivadas analiticas de primeira ord
  return (y);
}

float f3(float x,float y,float z,float w,float r){  //Funcao que calcula as derivadas analiticas de segunda ord
  return ((10*z - 18*r + 5*y - 5*w - 14.2)/10);
}

float f4(float x,float y,float z,float w,float r){  //Funcao que calcula as derivadas analiticas de segunda ord
  return (w);
}

String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  return conteudo;
}

void loop() {

    float h;

    Serial.print("Entre com o valor do passo 'h': ");
    
    while(1){ //leitura do valor de reset
      if (Serial.available() > 0){
      // Lê toda string recebida
      h = leStringSerial().toFloat();
      break;
      }
    }
    Serial.println(h);

    // Condicoes iniciais
    float y0 = 0;
    float z0 = 0;
    float w0 = 0;
    float r0 = 0;
    
    // Passo e dominio
    float x0 = 0;
    float xf = 10;
    int N = 0;
    float som = x0;

    while(1){
      N = N + 1;
      som = som + h;
      if(som == xf){
        break;
        }
    }

    N = N + 1;
    Serial.print("Numero de pontos = ");
    Serial.println(N);

    float x[N];
    float y[N];
    float z[N];
    float w[N];
    float r[N];
    int i = 0;
    
    
    y[1] = y0;
    z[1] = z0;
    w[1] = w0;
    r[1] = r0;  
    
    som = x0;
    for(i = 1; i<=N; i++){
      x[i] = som;
      som = som + h;   
    }

    int metodo;

    Serial.println("Escolha o Metodo:\n1->Euller Simples  2->Euller Modificado\n3->Ponto Central  4->Heun\n5->Runge-Kutta 3ªord  6->Runge-Kutta 4ªord\n");
    
    while(1){ //escolha do metodo
      if (Serial.available() > 0){
      // Lê toda string recebida
      metodo = leStringSerial().toInt();
      break;
      }
    }
    Serial.println(metodo);

    float a2= 0;float a3= 0;float a4= 0;float b21= 0;float b31= 0;float b32= 0;float b41= 0;float b42= 0;float b43= 0;float c1= 1;float c2 = 0;float c3= 0;float c4= 0;

    if(metodo == 1){
      float a2= 0;float a3= 0;float a4= 0;float b21= 0;float b31= 0;float b32= 0;float b41= 0;float b42= 0;float b43= 0;float c1= 1;float c2 = 0;float c3= 0;float c4= 0;
    }
    if(metodo == 2){
      float a2=1;float a3=0;float a4=0;float b21=1;float b31=0;float b32=0;float b41=0;float b42=0;float b43=0;float c1=1/2;float c2=1/2;float c3=0;float c4=0;
    }
    if(metodo == 3){
      float a2=1/2;float a3=0;float a4=0;float b21=1/2;float b31=0;float b32=0;float b41=0;float b42=0;float b43=0;float c1=0;float c2=1;float c3=0;float c4=0;
    }
    if(metodo == 4){
      float a2=2/3;float a3=0;float a4=0;float b21=2/3;float b31=0;float b32=0;float b41=0;float b42=0;float b43=0;float c1=1/4;float c2=3/4;float c3=0;float c4=0;
    }
    if(metodo == 5){
      float a2=1/2;float a3=1;float a4=0;float b21=1/2;float b31=-1;float b32=2;float b41=0;float b42=0;float b43=0;float c1=1/6;float c2=4/6;float c3= 1/6;float c4=0;
    }
    if(metodo == 6){
      float a2=1/2;float a3=1/2;float a4=1;float b21=1/2;float b31=0;float b32=1/2;float b41=0;float b42=0;float b43=1;float c1=1/6;float c4=1/6;float c3=2/6;float c2=2/6;
    }

    for(i=1; i<=(N-1); i++){
      float ky1 = f1(x[i],y[i],z[i],w[i],r[i]);
      float kz1 = f2(x[i],y[i],z[i],w[i],r[i]);
      float kw1 = f3(x[i],y[i],z[i],w[i],r[i]);
      float kr1 = f4(x[i],y[i],z[i],w[i],r[i]);
    
      float ky2 = f1(x[i]+ a2*h, y[i]+ b21*ky1*h, z[i]+ b21*kz1*h, w[i]+ b21*kw1*h, r[i]+ b21*kr1*h);
      float kz2 = f2(x[i]+ a2*h, y[i]+ b21*ky1*h, z[i]+ b21*kz1*h, w[i]+ b21*kw1*h, r[i]+ b21*kr1*h);
      float kw2 = f3(x[i]+ a2*h, y[i]+ b21*ky1*h, z[i]+ b21*kz1*h, w[i]+ b21*kw1*h, r[i]+ b21*kr1*h);
      float kr2 = f4(x[i]+ a2*h, y[i]+ b21*ky1*h, z[i]+ b21*kz1*h, w[i]+ b21*kw1*h, r[i]+ b21*kr1*h);
    
      float ky3 = f1(x[i]+ a3*h, y[i]+ b31*ky1*h+ b32*ky2*h, z[i]+ b31*kz1*h+ b32*kz2*h, w[i]+ b31*kw1*h+ b32*kw2*h, r[i]+ b31*kr1*h+ b32*kr2*h);
      float kz3 = f2(x[i]+ a3*h, y[i]+ b31*ky1*h+ b32*ky2*h, z[i]+ b31*kz1*h+ b32*kz2*h, w[i]+ b31*kw1*h+ b32*kw2*h, r[i]+ b31*kr1*h+ b32*kr2*h);
      float kw3 = f3(x[i]+ a3*h, y[i]+ b31*ky1*h+ b32*ky2*h, z[i]+ b31*kz1*h+ b32*kz2*h, w[i]+ b31*kw1*h+ b32*kw2*h, r[i]+ b31*kr1*h+ b32*kr2*h);
      float kr3 = f4(x[i]+ a3*h, y[i]+ b31*ky1*h+ b32*ky2*h, z[i]+ b31*kz1*h+ b32*kz2*h, w[i]+ b31*kw1*h+ b32*kw2*h, r[i]+ b31*kr1*h+ b32*kr2*h);
    
      float ky4 = f1(x[i]+ a4*h, y[i]+ b41*ky1*h+ b42*ky2*h+ b43*ky3*h, z[i]+ b41*kz1*h+ b42*kz2*h+ b43*kz3*h, w[i]+ b41*kw1*h+ b42*kw2*h+ b43*kw3*h, r[i]+ b41*kr1*h+ b42*kr2*h+ b43*kr3*h);
      float kz4 = f2(x[i]+ a4*h, y[i]+ b41*ky1*h+ b42*ky2*h+ b43*ky3*h, z[i]+ b41*kz1*h+ b42*kz2*h+ b43*kz3*h, w[i]+ b41*kw1*h+ b42*kw2*h+ b43*kw3*h, r[i]+ b41*kr1*h+ b42*kr2*h+ b43*kr3*h);
      float kw4 = f3(x[i]+ a4*h, y[i]+ b41*ky1*h+ b42*ky2*h+ b43*ky3*h, z[i]+ b41*kz1*h+ b42*kz2*h+ b43*kz3*h, w[i]+ b41*kw1*h+ b42*kw2*h+ b43*kw3*h, r[i]+ b41*kr1*h+ b42*kr2*h+ b43*kr3*h);
      float kr4 = f4(x[i]+ a4*h, y[i]+ b41*ky1*h+ b42*ky2*h+ b43*ky3*h, z[i]+ b41*kz1*h+ b42*kz2*h+ b43*kz3*h, w[i]+ b41*kw1*h+ b42*kw2*h+ b43*kw3*h, r[i]+ b41*kr1*h+ b42*kr2*h+ b43*kr3*h);
    
      y[i+1] = y[i] + (c1*ky1 + c2*ky2 + c3*ky3 + c4*ky4)*h;
      z[i+1] = z[i] + (c1*kz1 + c2*kz2 + c3*kz3 + c4*kz4)*h;
      w[i+1] = w[i] + (c1*kw1 + c2*kw2 + c3*kw3 + c4*kw4)*h;
      r[i+1] = r[i] + (c1*kr1 + c2*kr2 + c3*kr3 + c4*kr4)*h;
    }
    

    for(i = 1; i<=N; i++){
      Serial.print("\ny = ");
      Serial.println(y[i]);
      Serial.print("z = ");
      Serial.println(z[i]);
      Serial.print("w = ");
      Serial.println(w[i]);
      Serial.print("r = ");
      Serial.println(r[i]);
      Serial.print("x = ");
      Serial.println(x[i]);
    }

    float reset;

    Serial.println("\nEnvie qualquer caracter para reiniciar o codigo!!!\n");
    
    while(1){ //leitura do valor de reset
      if (Serial.available() > 0){
      // Lê toda string recebida
      reset = leStringSerial().toFloat();
      break;
      }
    }
    
}
