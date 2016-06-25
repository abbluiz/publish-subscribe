## -- Primeiro Trabalho de Estrutura de Dados I: COMPLETO (100%) E ENTREGUE [RECEBIDO: 10/10] --

###| Usando git via terminal |

### --> Instalando
 
> sudo apt-get install git

### --> Iniciando e tendo acesso ao repositório de códigos.

-> O comando a seguir cria uma pasta com o nome trabalho_1 (onde o terminal estiver aberto) e os códigos serão carregados nela.

> git clone https://<seu-usuario-bitbucket>@bitbucket.org/destruindo_ed/trabalho_1.git

###### ! Abrir terminal dentro da pasta trabalho_1 é interessante !

### --> Modificando arquivos do repositório

-> Primeiro edite o arquivo em si e o salve.

-> Para adicionar um arquivo/atualizar ao repositório: O código a seguir **adiciona** o arquivo localmente no git.

> git add <caminhodoarquivo>

-> Para fazer o mesmo que o código anterior, porém para todos os arquivos modificados no repositório de uma vez:

> git add *

-> O comando a seguir **deleta** um arquivo no git localmente.

> git rm <caminhodoarquivo>

-> O comando a seguir **adiciona um comentário** respectivo a alteração feita no(s) arquivo(s) alterado(s) localmente.

> git commit -m "<comentario>"

-> O comando a seguir **publica** todas as alterações locais no repositório **online** (na branch especificada). No lugar de (nome-da-branch) é necessário colocar master caso a alteração seja feita na branch principal do repositório ou o nome da branch caso seja outro (ver Significado e criação de branchs).

> git push origin <nome-da-branch>

### --> Significado e criação de branchs

-> O comando a seguir **cria uma nova branch** do repositório. Todo repositório tem uma vertente principal chamada master. Se criam novas vertentes (chamadas de branchs do repositório) para organizar melhor as partes do desenvolvimento. Por exemplo, uma vertente para tal .h ou .c por questões de organização.

> git branch <nome-da-branch-nova>

-> O comando a seguir **acessa** (vai para) a branch indicada no comando.

> git checkout <nome-da-branch>

-> O comando a seguir **lista** as branchs existentes no repositório local e em qual branch está.

> git branch

-> O comando a seguir **deleta** uma branch localmente. Note que o argumento -d somente deleta caso não haja nenhuma pendência naquela branch. Pra deletar "na marra" use -D.

> git branch -d <nome-da-branch>

-> Para **deletar** uma branch no repositório remoto (**online**) (repare o símbolo **:** antes do nome da branch):

> git push origin :<nome-da-branch>

### --> Comandos adicionais:

-> O comando a seguir mostra o log de todas as alterações do repositório.

> git log

-> O comando a seguir atualiza o repositório na sua pasta local da branch que você está.

> git pull

[Clique aqui para um tutorial bem fácil de git](http://rogerdudler.github.io/git-guide/index.pt_BR.html)

###### ! Conforme os contribuidores aprendam mais comandos, seria interessante atualizar esse arquivo com as descrições !