# Braço Robótico
<img width="940" height="704" alt="image" src="https://github.com/user-attachments/assets/df08095a-322f-430e-bb48-e2f5b39d149b" />

## Introdução
O projeto inicialmente tinha como objetivo desenvolver uma máquina de pelúcia completa, porém essa proposta se mostrou altamente trabalhosa e excessivamente centrada na parte mecânica e de construção, desviando do foco principal da disciplina, que envolve computação aplicada à física.  

Diante disso, e considerando que o professor disponibilizou um molde pronto para o braço robótico, optou-se por redirecionar o projeto. A partir dessa mudança, o novo objetivo passou a ser implementar, no braço robótico controlado por um ESP32, a lógica de funcionamento do gancho de uma máquina de pelúcia, preservando a essência da ideia original, mas em uma forma mais viável, prática e alinhada ao propósito educacional do trabalho.

## Objetivos
- Desenvolver um braço robótico controlado por um ESP32 capaz de movimentar quatro servomotores de forma precisa e independente, permitindo controlar articulações como base, elevador, guindaste e garra.  
- Automatizar os movimentos do braço robótico por meio de sequências programadas, permitindo que os servomotores executem tarefas repetitivas de forma precisa, sem necessidade de controle manual contínuo.

## Método de Execução

1. **Instalar Arduino IDE**  
   Instalar a Arduino IDE para escrever, editar e enviar o código ao ESP32. A IDE fornece suporte a placas externas, monitores seriais e bibliotecas essenciais para o desenvolvimento do projeto.

2. **Instalar placa ESP32**  
   Adicionar o pacote de suporte à placa ESP32 no Gerenciador de Placas da IDE, habilitando configurações específicas como frequência de CPU, velocidade da porta serial e modo de upload.

3. **Instalar biblioteca ESP32Servo**  
   A biblioteca permite o controle adequado dos servomotores, simplificando a movimentação precisa dos servos no braço robótico.

4. **Clonar GitHub**  
   Clonar o repositório para obter o código fonte e futuras atualizações:  
   ```bash
   git clone https://github.com/rMarcosDSS/Projeto-CFA
   ```

5. **Configuração da placa e porta serial**  
   Selecionar corretamente o modelo da placa e configurar a porta serial utilizada na conexão USB.

6. **Montagem**  
   Encaixar todas as partes do braço robótico disponibilizadas pelo molde, fixando cada servomotor de forma firme e alinhada.

7. **Ajuste de Wi-Fi e parâmetros do código**  
   Configurar nome da rede, senha e portas no código, além de limites de ângulo ou posições pré-definidas, se necessário.

8. **Importar código no ESP32**  
   Compilar e enviar o arquivo `BracoRobotico.ino` via Arduino IDE para permitir que o braço execute movimentos e responda às rotas HTTP.

9. **Teste individual dos servos**  
   Testar cada servo individualmente para confirmar funcionamento correto, ângulos adequados e estabilidade de alimentação.

## Materiais Necessários
- ESP32  
- 4 Servos SG-90  
- Estrutura de braço robótico  
- Cabo USB compatível com ESP32  
- Fonte de energia compatível com USB para ESP32  
- Fonte 5V para os servos  
- 13 jumpers  
- 1 Protoboard  

## Montagem
<img width="566" height="484" alt="image" src="https://github.com/user-attachments/assets/10324305-8828-4de7-836a-158c9b0a95ec" />

| Componente | Pino do Servo | Cor do Fio | Conexão no ESP32 / Fonte |
|------------|---------------|------------|-------------------------|
| Servos (1-4) | Sinal | Laranja | GPIO (W-Z) fio azul |
| Servos (1-4) | VCC | Vermelho | +5V da fonte externa |
| Servos (1-4) | GND | Preto | GND da fonte externa |
| ESP32 | GND | — | Conectado ao GND da fonte externa |
| ESP32 | GPIO X/Y/Z/W | — | Enviam sinal PWM para os servos |

> A configuração garante funcionamento correto dos servos, combinando sinais PWM independentes com alimentação externa adequada. O GND comum entre ESP32 e fonte é essencial para estabilidade e interpretação correta dos sinais.

## Manual do Usuário
| Rota | Efeito causado |
|------|----------------|
| /setServo | Ajusta o ângulo de um servo específico |
| /salvar | Armazena posições atuais dos servos (A ou B) |
| /executar | Executa a sequência automática entre posições salvas |
| /parar | Interrompe execução automática |

## Conteúdo do Projeto

### BracoRobotico.ino
Responsável por criar a rede Wi-Fi própria (modo Access Point) para controlar o braço remotamente via navegador. Inicializa comunicação serial, configura servos e define rotas HTTP.

### ServosController.h / ServosController.cpp
Controlam os servos, definem ângulos iniciais e limites de movimento, permitem mover e salvar posições individuais ou executar sequências automáticas.

### WebInterface.h / WebInterface.cpp
Configuram rede Wi-Fi, criam a interface web com sliders e botões, e definem as rotas HTTP que permitem controle remoto e salvamento de posições.

### Página web responsável por controlar o braço robótico
<img width="628" height="514" alt="image" src="https://github.com/user-attachments/assets/fb7ecc26-7647-4f95-af94-b39cc1f7336f" /> 

## Testes Principais
**Movimento Livre do Braço:** Teste individual de cada servo, verificando alcance, suavidade, resposta e alimentação estável.

**Automação de Tarefas:** Execução automática entre posições A e B, verificando precisão, interpretação correta dos comandos e estabilidade do ESP32.

**Testes Gerais:** Avaliação das rotas HTTP, salvamento de posições, sequência automática, alcance de ângulos, estabilidade da alimentação e precisão dos movimentos.

## Conclusão
O braço robótico foi implementado com sucesso, controlando quatro servos de forma independente e realizando tarefas automatizadas. O sistema responde corretamente às rotas definidas, armazena posições, executa movimentos automáticos entre pontos programados e mantém estabilidade graças à alimentação externa. Os testes confirmaram a precisão, confiabilidade e aplicação prática de conceitos de computação aplicada à física.

## Comentários
O projeto inicialmente utilizou MicroPython e Thonny, mas devido a problemas com drivers SG90, foi migrado para Arduino IDE. A alimentação separada dos servos eliminou quedas de tensão e reinicializações, garantindo operação estável e consistente do ESP32.

## Referências
- [Datasheet SG90](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)  
- [YouTube Tutorial](https://www.youtube.com/watch?v=Q9JOKQaIR1w&t=67s)  
- [RobotArm GitHub](https://github.com/un0038998/RobotArm)  
- [RobotArmCar GitHub](https://github.com/un0038998/RobotArmCar)  
- [Google Docs](https://docs.google.com/document/d/e/2PACX-1vQ4z7ercMLMgiqyDeGiRy27XtwrC17XTXDxz47BFIjvwmiIZ-8aauLrzXGYXuMBRe32CPwSDNsyA-et/pub)  
- [Drive PDF](https://drive.google.com/file/d/1Rs8wIgR3nklvCN3fQDzlYGLvO8Wg3h3p/view)
