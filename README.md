Este projeto é um Analisador Léxico (Scanner) para a linguagem de programação C- (um subconjunto do C, conforme especificado no PDF do projeto).

O programa é escrito em linguagem C e tem como objetivo ler um arquivo de código-fonte C- (.c-) e exibir na tela todos os tokens (marcas) e seus respectivos lexemas (cadeias de caracteres) encontrados.
Este programa foi desenvolvido, compilado e testado utilizando o seguinte ambiente:
Editor: Visual Studio Code
Sistema: Windows
Compilador: GCC (através da suíte MinGW-w64)
Terminal: PowerShell (integrado ao VS Code)

Antes de executar, você precisa compilar o código-fonte scanner_c_menos.c para gerar um arquivo executável.
Abra um terminal e navegue ate a pasta do seu arquivo so scanner/varredura, e execute o comando de compilaçao do gcc: "gcc scanner_c_menos.c -o SistVarredura.exe"
Isso criará o arquivo SistVarredura.exe. Para os exemplos de execução, é recomendado mover este .exe para uma pasta de fácil acesso (como uma pasta output dentro do projeto).

O programa precisa saber qual arquivo .c- ele deve ler. Existem duas maneiras de fazer isso:
Método 1: Usando Argumentos de Linha de Comando
Você simplesmente informa o nome do arquivo de teste no momento da execução.
Exemplo: O arquivo de teste está na MESMA pasta do .exe
Coloque seu arquivo de teste (ex: teste.c-) na mesma pasta que o SistVarredura.exe.
Abra o terminal PowerShell nessa pasta.
Execute o programa passando o nome do arquivo como argumento:
" & .\'SistVarredura.exe' teste.c- "

Segundo exemplo: O arquivo de teste está em OUTRA pasta
Você pode executar o programa informando o caminho (relativo ou absoluto) do arquivo de teste.
Exemplo (Caminho Relativo): Se o .exe está em output e o teste.c- está na pasta anterior (Compiladores):
# Estando na pasta 'output':
& .\'SistVarredura.exe' ..\teste.c-
Exemplo (Caminho Absoluto): Você pode informar o caminho completo do arquivo de teste, não importa onde ele esteja.
# Estando na pasta 'output':
& .\'SistVarredura.exe' "C:\Users\arthu\OneDrive\Documentos\outro_teste.c-"

