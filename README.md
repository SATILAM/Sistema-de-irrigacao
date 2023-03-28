# Sistema-de-irrigação
Programa para controlar um sistema de irrigação usando um microcontrolador Arduino.

Este foi o meu trabalho de conclusão do Curso de Técnico em Mecatrônia no Senai-GO em Julho de 2014.

O programa utiliza vários componentes eletrônicos, como um relógio em tempo real (RTC), uma tela de LCD, botões e algumas válvulas e
uma bomba para controlar a irrigação.

O programa começa definindo um array t1 de sete elementos com valores zero, que será usado para armazenar os tempos em que as válvulas devem ser ligadas e desligadas. 

Em seguida, define-se uma variável dd para ser usada como atraso na apresentação dos dados do temporizador. 

Também é incluída a biblioteca LiquidCrystal, a biblioteca Wire, a biblioteca EEPROM e a biblioteca RTClib.

A variável RTC é declarada como um objeto do tipo RTC_DS1307, e a variável state é inicializada com o valor 1. 

Em seguida, é criado um objeto lcd do tipo LiquidCrystal usando os pinos 12, 11, 5, 4, 3 e 2.

A função ArrumaZero é definida para adicionar um zero à esquerda dos valores de hora e minuto que são menores que 10.

Na função setup(), os pinos dos botões, da válvula 1, da válvula 2 e da bomba são definidos como entradas ou saídas.

O pull-up interno dos botões é ativado usando a função digitalWrite. Em seguida, é verificado se o relógio em tempo real está funcionando; 
caso contrário, o relógio é ajustado para a data e hora atuais.

Os valores das horas e minutos de início e fim da irrigação são lidos a partir da EEPROM e armazenados nas variáveis horini, minini, horfim e minfim.

No loop principal (loop()), um switch-case é usado para selecionar a tela atual do programa (1 a 6). 

Em cada tela, um outro switch-case é usado para verificar qual botão foi pressionado e agir de acordo com o botão pressionado.

As telas mostram as seguintes informações:

Tela 1: mostra o tempo restante para a próxima irrigação.
Tela 2: permite a configuração da hora de início da irrigação.
Tela 3: permite a configuração dos minutos de início da irrigação.
Tela 4: permite a configuração da hora de fim da irrigação.
Tela 5: permite a configuração dos minutos de fim da irrigação.
Tela 6: mostra o tempo restante para o fim da irrigação.

As funções Set_state e CheckButton são usadas para mudar de tela e verificar qual botão foi pressionado, respectivamente. 

As funções EEPROM.write são usadas para gravar as horas e minutos de início e fim da irrigação na EEPROM. 
As funções digitalWrite são usadas para ligar ou desligar as válvulas e a bomba de acordo com o tempo programado.

Em resumo, este programa é um sistema completo de irrigação controlado por um microcontrolador Arduino e,
é capaz de controlar várias válvulas e uma bomba para irrigar plantas de acordo com um horário pré-definido.




![photo2 (1)](https://user-images.githubusercontent.com/101275634/228253810-374300ab-9aaa-441f-aa41-73b1dad46442.jpg)




![img irrig](https://user-images.githubusercontent.com/101275634/228252556-c3c5f44c-146b-45da-a1ef-fb3b15ddc725.JPG)
