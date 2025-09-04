# Sistema de Automação e Controle de Ar-Condicionados

Este repositório contém códigos e bibliotecas para automação e controle de aparelhos de ar-condicionado utilizando **ESP32** ou **ESP8266**.

---
## ⚙️ Configuração do Ambiente

### 🔹 Instalação do suporte ao ESP32
1. Abra o **Arduino IDE**.  
2. Vá em: `Arquivo > Preferências`.  
3. Em **URLs do Gerenciador de Placas Adicionais**, adicione:
```bash
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
5. Vá em: `Ferramentas > Placa > Gerenciador de Placas`.  
6. Procure por **ESP32** e instale.

---

### 🔹 Instalação do suporte ao ESP8266
1. Abra o **Arduino IDE**.  
2. Vá em: `Arquivo > Preferências`.  
3. Em **URLs do Gerenciador de Placas Adicionais**, adicione:
```bash
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
5. Vá em: `Ferramentas > Placa > Gerenciador de Placas`.  
6. Procure por **ESP8266** e instale.

---

## 📦 Instalação das Bibliotecas

Todas as bibliotecas necessárias estão disponíveis neste repositório, dentro das pastas correspondentes.

Para instalar manualmente:  
1. No Arduino IDE, vá em: `Sketch > Incluir Biblioteca > Adicionar Biblioteca .ZIP`.  
2. Selecione o arquivo `.zip` da biblioteca desejada.  
3. Repita o processo para todas as bibliotecas necessárias (ESP32 ou ESP8266, conforme o projeto).

---

## 🚀 Uso

- Se for utilizar **ESP32**, compile o código específico para ele.  
- Se for utilizar **ESP8266**, compile o código específico para ele.  

> ⚠️ Certifique-se de instalar as bibliotecas corretas para a placa escolhida.

---

## 📖 Observações
- Testado no **Arduino IDE** mais recente.  
- Compatível com **ESP32 DevKit V1** e **ESP8266 NodeMCU**.  
- Para dúvidas ou melhorias, abra uma *issue* neste repositório.
****
