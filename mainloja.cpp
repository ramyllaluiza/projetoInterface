#include "mainloja.h"
#include "ui_mainloja.h"

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja),
      inclLivro(nullptr),
      inclCD(nullptr),
      inclDVD(nullptr),
      X(),
      total_itens(nullptr)

{
    ui->setupUi(this);
    inclLivro = new IncluirLivro(this);
    inclCD = new IncluirCD(this);
    inclDVD = new IncluirDVD(this);
    total_itens = new QLabel(this);

    ui->statusbar->insertWidget(0, new QLabel("Total de itens: "));

    connect(inclLivro, & IncluirLivro::signIncluirLivro, this, & MainLoja::slotIncluirLivro);
    connect(inclCD, & IncluirCD::signIncluirCd, this, & MainLoja::slotIncluirCD);
    connect(inclDVD, & IncluirDVD::signIncluirDvd, this, & MainLoja::slotIncluirDVD);

    ui->statusbar->insertWidget(1, total_itens);

    ui->tableLivros->setStyleSheet( "QHeaderView::section { text-align:center }"
                                    "QHeaderView::section { background-color:lightgray }");

    ui->tableCds->setStyleSheet( "QHeaderView::section { text-align:center }"
                                 "QHeaderView::section { background-color:lightgray }");

    ui->tableDvds->setStyleSheet( "QHeaderView::section { text-align:center }"
                                  "QHeaderView::section { background-color:lightgray }");

    ui->tableLivros->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableLivros->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableLivros->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableCds->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableCds->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableCds->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableDvds->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableDvds->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableDvds->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    exibirLivros();
    exibirCDs();
    exibirDVDs();
}

MainLoja::~MainLoja()
{
    delete ui;
}

void MainLoja::exibirLivros()
{
    ui->tableLivros->clearContents();
    ui->tableLivros->setRowCount(X.getNumLivro());

    for(int i = 0; i <= (X.getNumLivro()-1); i++){
        Livro L = X.getLivro(i);
        QLabel* var_nome = new QLabel(L.getNome().c_str());
        QLabel* var_preco = new QLabel(QString::number(L.getPreco(),'f',2));
        QLabel* var_autor = new QLabel(L.getAutor().c_str());

        var_nome->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        var_preco->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        var_autor->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

        ui->tableLivros->setCellWidget(i,0, var_nome);
        ui->tableLivros->setCellWidget(i,1, var_preco);
        ui->tableLivros->setCellWidget(i,2, var_autor);
    }

    total_itens->setNum(X.getNumLivro()+X.getNumCD()+X.getNumDVD());
}

void MainLoja::exibirCDs()
{
    ui->tableCds->clearContents();
    ui->tableCds->setRowCount(X.getNumCD());

    for(int i = 0; i <= (X.getNumCD()-1); i++){
        CD C = X.getCD(i);
        QLabel* var_nome = new QLabel(C.getNome().c_str());
        QLabel* var_preco = new QLabel(QString::number(C.getPreco(),'f',2));
        QLabel* var_n_faixas = new QLabel(QString::number(C.getNumFaixas()));

        var_nome->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        var_preco->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        var_n_faixas->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

        ui->tableCds->setCellWidget(i,0, var_nome);
        ui->tableCds->setCellWidget(i,1, var_preco);
        ui->tableCds->setCellWidget(i,2, var_n_faixas);
    }

    total_itens->setNum(X.getNumLivro()+X.getNumCD()+X.getNumDVD());
}

void MainLoja::exibirDVDs()
{
    ui->tableDvds->clearContents();
    ui->tableDvds->setRowCount(X.getNumDVD());

    for(int i = 0; i <= (X.getNumDVD()-1); i++){
        DVD D = X.getDVD(i);
        QLabel* var_nome = new QLabel(D.getNome().c_str());
        QLabel* var_preco = new QLabel(QString::number(D.getPreco(),'f',2));
        QLabel* var_duracao = new QLabel(QString::number(D.getDuracao()));

        var_nome->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        var_preco->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        var_duracao->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

        ui->tableDvds->setCellWidget(i,0, var_nome);
        ui->tableDvds->setCellWidget(i,1, var_preco);
        ui->tableDvds->setCellWidget(i,2, var_duracao);
    }

    total_itens->setNum(X.getNumLivro()+X.getNumCD()+X.getNumDVD());
}



void MainLoja::on_tableLivros_cellDoubleClicked(int row)
{
    if(row <= X.getNumLivro()-1){
        if(X.excluirLivro(row)) exibirLivros();
    }

}

void MainLoja::on_tableCds_cellDoubleClicked(int row)
{
    if(row <= X.getNumCD()-1){
        if(X.excluirCD(row)) exibirCDs();
    }

}

void MainLoja::on_tableDvds_cellDoubleClicked(int row)
{
    if(row <= X.getNumDVD()-1){
        if(X.excluirDVD(row)) exibirDVDs();
    }
}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
    Livro novo_livro(nome.toStdString() , (preco.toFloat()), autor.toStdString());

    if(novo_livro.getNome() != "" && novo_livro.getAutor() != "" && novo_livro.getPreco()>0){
        X.incluirLivro(novo_livro);
        exibirLivros();
        return;
    }
    QMessageBox::critical(this, "Livro invalido", "Nao foi possivel incluir o livro: \nNome="+nome.toLatin1() + "\nPreco=" + preco.toLatin1() + "\nAutor=" + autor.toLatin1());

}
void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas)
{

    CD novo_CD(nome.toStdString() , (preco.toFloat()), numfaixas.toFloat());

    if(novo_CD.getNome() != "" && novo_CD.getNumFaixas()>0 && novo_CD.getPreco()>0){
        X.incluirCD(novo_CD);
        exibirCDs();
        return;
    }
    QMessageBox::critical(this, "CD invalido", "Nao foi possivel incluir o CD: \nNome="+nome.toLatin1() + "\nPreco=" + preco.toLatin1() + "\nNum faixas=" + numfaixas.toLatin1());
}
void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
    DVD novo_DVD(nome.toStdString() , (preco.toFloat()), duracao.toFloat());

    if(novo_DVD.getNome() != "" && novo_DVD.getDuracao()>0 && novo_DVD.getPreco()>0){
        X.incluirDVD(novo_DVD);
        exibirDVDs();
        return;
    }
    QMessageBox::critical(this, "DVD invalido", "Nao foi possivel incluir o DVD: \nNome="+nome.toLatin1() + "\nPreco=" + preco.toLatin1() + "\nNum Duracao=" + duracao.toLatin1());

}

void MainLoja::on_actionLer_triggered()
{
    QString fileName = QFileDialog::
        getOpenFileName(this,
                        "Open File",
                        QDir::homePath(),
                        "Text Files (*.txt)");

    if (!fileName.isEmpty())
    {
        if(!X.ler(fileName.toStdString())) QMessageBox::critical(this, "Arquivo invalido", "Ocorreu um erro na leitura do arquivo.");

        exibirLivros();
        exibirCDs();
        exibirDVDs();
    }
}
void MainLoja::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::
        getSaveFileName(this,
                        "Save File",
                        QDir::homePath(),
                        "Text Files (*.txt)");

    if (!fileName.isEmpty())
    {
        if(!X.salvar(fileName.toStdString())) QMessageBox::critical(this, "Arquivo invalido", "Ocorreu um erro no salvamento do arquivo.");
    }
}


void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainLoja::on_actionIncluir_Livro_triggered()
{
    (*inclLivro).clear();
    (*inclLivro).setVisible(true);
}


void MainLoja::on_actionIncluir_CD_triggered()
{
    (*inclCD).clear();
    (*inclCD).setVisible(true);
}


void MainLoja::on_actionIncluir_DVD_triggered()
{
    (*inclDVD).clear();
    (*inclDVD).setVisible(true);
}

