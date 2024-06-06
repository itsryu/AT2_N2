<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">

<body>
    <div id="container">
        <div align="center" style="display: inline_block">
            <h1>Sistema de Playlist</h1>
            <p>Este é um projeto de console desenvolvido utilizando a linguagem de programação C para o gerenciamento
                (Inserção, Remoção e Busca) de músicas em uma playlist, permitindo também, que o usuário avance e retorne as músicas. Contém
                um menu interativo onde o usuário tem a liberdade para realizar as ações.</p>
        </div>
        <div>
            <h2>Funcionalidades</h2>
            <ul>
                <li>Exibição da playlist pela ordem de cadastro;</li>
                <li>Exibição da playlist ordenada pelo nome das músicas;</li>
                <li>Inserção de novas músicas;</li>
                <li>Remoção de uma música;</li>
                <li>Busca por uma música;</li>
                <li>Avançar para próxima música;</li>
                <li>Retornar a música anterior;</li>
            </ul>
            <h2>Como Usar</h2>
            <ol>
                <li>
                    <strong>Clonar o repositório:</strong> Para clonar o repositório, execute o seguinte comando em seu
                    terminal (Obs: necessário ter o <a href="https://git-scm.com/downloads">git</a> instalado em sua
                    máquina):
                    <pre><code>git clone https://github.com/itsryu/AT2_N2.git</code></pre>
                </li>
                <li>
                    <strong>Compilação:</strong> Vá para a pasta AT2_N2 dentro de onde o projeto foi clonado e execute o arquivo windows.bat (Windows):
                    <pre><code>windows.bat</code></pre>
                </li>
                <li>
                    <strong>Compilação:</strong> Ou se quiser compilar utilizando linha de comando abra um terminal na pasta AT2_N2 dentro de onde o projeto foi clonado e compile o
                    programa utilizando o GCC (GNU Compiler Collection):
                    <pre><code>gcc ./functions/functions.c ./functions/menu.c ./main.c -o main.exe</code></pre>
                </li>
                <li>
                    <strong>Execução:</strong> Após a compilação, execute o arquivo 'main.exe' para inicializar o
                    programa.
                    <pre><code>main.exe</code></pre>
                </li>
                <li><strong>Interagindo com o programa:</strong> Siga as instruções do menu para realizar as ações
                    desejadas.</li>
            </ol>
            <h2>Ferramentas de desenvolvimento utilizadas</h2>
            <ol>
                <li><strong>Visual Studio Community 2022</strong> (Utilizada para o desenvolvimento e depuração do
                    código)</li>
                <li><strong>GitHub</strong> (Utilizada para o versionamento)</li>
            </ol>
        </div>
    </div>
</body>

</html>