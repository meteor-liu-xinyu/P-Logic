#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    mode = 2;

    this->modechooseWidget = new ModeChoose;

    ui->textEdit->setReadOnly(true);

    connect(this->modechooseWidget,&ModeChoose::modeSelected,this,&MainWidget::receiveModeSelected);

//    qDebug() << "now mode = " << mode;

    connect(ui->lineEdit,&QLineEdit::returnPressed,this,&MainWidget::on_commitButton_clicked);

    connect(this,&this->errorInput,this,&MainWidget::receiveErrorInput);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_inputSettingButton_clicked()
{
    this->modechooseWidget->show();
    resetLineEdit();
    ui->lineEdit->setText("");
}

void MainWidget::keyPressEvent(QKeyEvent *k)
{
//    qDebug() << k->key();
    if (k->key() == Qt::Key_Backspace || k->key() == Qt::Key_Delete)
    {
        resetLineEdit();
    }
    else if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
    else if (k->modifiers() == Qt::ControlModifier)
    {
        if (k->key() == Qt::Key_O)
        {
            on_inputSettingButton_clicked();
        }
        else if (k->key() == Qt::Key_S)
        {
            on_symbolButton_clicked();
        }
        else if (k->key() == Qt::Key_H)
        {
            on_helpButton_clicked();
        }
        else if (k->key() == Qt::Key_K)
        {
            on_shortcartButton_clicked();
        }
        else if (k->key() == Qt::Key_1)
        {
            on_truthtableButton_clicked();
        }
        else if (k->key() == Qt::Key_2)
        {
            on_cnfButton_clicked();
        }
        else if (k->key() == Qt::Key_3)
        {
            on_dnfButton_clicked();
        }
        else if (k->key() == Qt::Key_4)
        {
            on_kmapButton_clicked();
        }
        else if (k->key() == Qt::Key_5)
        {
            on_simplifyButton_clicked();
        }
    }
}

void MainWidget::receiveModeSelected(int mode)
{
    this->mode = mode;

    ui->lineEdit->setFocus();

    if (mode == 6)
    {
        tableinput = new TableInput;
        tableinput->show();
        connect(tableinput,&TableInput::sentinput,this,MainWidget::getTableinput);
    }
//    qDebug() << "now mode = " << mode;
}

void MainWidget::InitMode()
{
    this->modechooseWidget->show();
}

void MainWidget::on_symbolButton_clicked()
{
    symbol = new Symbol;
    symbol->show();
    connect(this->symbol,&Symbol::sentkey,this,&MainWidget::receiveKey);
}

void MainWidget::receiveKey(QString keyname)
{
    QString tempinput = ui->lineEdit->text();
    if (mode != 6)
    {
        if (mode == 1)
        {
            if (keyname == "not1")
                tempinput.append('~');
            else if (keyname == "and1")
                tempinput.append(QChar(0x2227));
            else if (keyname == "or1")
                tempinput.append(QChar(0x2228));
        }
        else if (mode == 2)
        {
            if (keyname == "not2")
                tempinput.append('`');
            else if (keyname == "and2")
                tempinput.append(QChar(0xD7));
            else if (keyname == "or2")
                tempinput.append('+');
        }
        else if (mode == 3 || mode == 4)
        {
            if (keyname == "equal")
                tempinput.append('=');
            else if (keyname == "comma")
                tempinput.append(',');
        }
        if (keyname == "leftbracket")
            tempinput.append('(');
        else if (keyname == "rightbracket")
            tempinput.append(')');
        else if (keyname == "sum" && mode == 4)
            tempinput.append(QChar(0x2211));
        else if (keyname == "prod" && mode == 3)
            tempinput.append(QChar(0x220F));
        else if (keyname == "key_M" && mode == 3)
            tempinput.append('M');
        else if (keyname == "key_m" && mode == 4)
            tempinput.append('m');
        else if (keyname == "key_D")
            tempinput.append('D');
        if (mode == 1 || mode == 2)
        {
            if (keyname == "condition")
                tempinput.append(QChar(0x2192));
            else if (keyname == "doublecondition")
                tempinput.append(QChar(0x2194));
            else if (keyname == "key_xor")
                tempinput.append(QChar(0x2295));
            else if (keyname == "nand")
                tempinput.append(QChar(0x2191));
            else if (keyname == "nor")
                tempinput.append(QChar(0x2193));
        }
        else if (keyname == "key_A")
            tempinput.append('A');
        else if (keyname == "key_B")
            tempinput.append('B');
        else if (keyname == "key_C")
            tempinput.append('C');
        else if (keyname == "key_X")
            tempinput.append('X');
        else if (keyname == "key_Y")
            tempinput.append('Y');
        else if (keyname == "key_Z")
            tempinput.append('Z');
        else if (keyname == "key_W")
            tempinput.append('W');
    }
    ui->lineEdit->setText(tempinput);
}

void MainWidget::on_helpButton_clicked()
{
    helpinfomation = new HelpInfomation;
    helpinfomation->show();
}

void MainWidget::on_commitButton_clicked()
{
    InitAll();
    input = ui->lineEdit->text();

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ') // 去除空格
        {
            input.remove(i, 1);
            i--;
        }
    }
    if (input.size() == 0) // 判断输入是否为空
    {
        QMessageBox::warning(this,"错误","输入为空");
        emit errorInput(1);
        return;
    }

    if (TransLegal() == false)
    {
        return;
    }
    ui->lineEdit->setText(initialinput);

    inputProcess();
    FindArg(); // 获取命题变元名
    BuildHashTable();

    calculate = new Calculate;
    calculate->Set(input,ArgName,ToBin,mode,unrelatedItems,If_unrelated);
    Value = calculate->Cal();
    If_unrelated = calculate->getUnrelated();
    delete calculate;
    if (Value.empty())
    {
        emit errorInput(2);
        return;
    }

    ui->lineEdit->setStyleSheet("background-color: #98FB98;"); // 设置背景为浅绿色

    connect(ui->lineEdit, &QLineEdit::selectionChanged, this, MainWidget::resetLineEdit);

    connect(ui->lineEdit,&QLineEdit::textChanged,this,MainWidget::resetLineEdit);
}

void MainWidget::receiveErrorInput(int errorcode)
{
    qDebug() << "error input" << errorcode;
    InitAll();
}

void MainWidget::receivecalErrorInput(int errorcode)
{
    qDebug() << "error input" << errorcode;
    InitAll();
}

void MainWidget::InitAll()
{
    input.clear();
    initialinput.clear();
    ArgName.clear();
    Argnum = 0;
    Value.clear();
    PI.clear();
    NF.clear();
    kanuo.clear();
    ToBin.clear();
    ToDec.clear();
    unrelatedItems.clear();
    If_unrelated.clear();

    calculate = NULL;
    paradigms = NULL;
    maketruthtable = NULL;
    calkanuo = NULL;
    kmap = NULL;
    tableinput = NULL;
    symbol = NULL;
    helpinfomation = NULL;
    keybordshortcut = NULL;
}

bool MainWidget::TransLegal()
{
    // 将中文括号转换为英文括号
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == QChar(0xFF08)) // 中文左括号
        {
            input[i] = '(';
        }
        else if (input[i] == QChar(0xFF09)) // 中文右括号
        {
            input[i] = ')';
        }
        else if (input[i] == '\'') // 英文单引号
        {
            input[i] = '`';
        }
        else if (input[i] == QChar(0x2018)) // 中文左单引号
        {
            input[i] = '`';
        }
        else if (input[i] == QChar(0x2019)) //中文右单引号
        {
            input[i] = '`';
        }
        else if (input[i] == QChar(0xFF0C)) // 中文逗号
        {
            input[i] = ',';
        }
        else if (input[i] == '^') // 合取符号
        {
            input[i] = QChar(0x2227);
        }
        else if (input[i] == 'v') // 析取符号
        {
            input[i] = QChar(0x2228);
        }
        else if (input[i] == '*') // 乘号符号
        {
            input[i] = QChar(0xD7);
        }
        else if (input[i] == '[') // 与非符号
        {
            input[i] = QChar(0x2191);
        }
        else if (input[i] == ']') // 或非符号
        {
            input[i] = QChar(0x2193);
        }
        else if (input[i] == '@') // 与非符号
        {
            input[i] = QChar(0x2295);
        }
        else if (input[i] == '>') // 条件符号
        {
            input[i] = QChar(0x2192);
        }
        else if (input[i] == '<') // 双条件符号
        {
            input[i] = QChar(0x2194);
        }
    }

    int count = 0; // 括号匹配
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == '(')
        {
            count++;
        }
        else if (input[i] == ')')
        {
            count--;
            if (count < 0)
            {
                QMessageBox::warning(this,"错误","括号不匹配");
                emit errorInput(17);
                return false;
            }
        }
        else if (input[i] == 'V') // 将大写字母V转换为析取符号
        {
            input[i] = QChar(0x2228);
        }
        else if (input[i] >= 'a' && input[i] <= 'z') // 将小写字母转换为大写字母
        {
            input[i] = input[i].toUpper();
        }
        if (input[i] == 'M' && (mode == 4 || mode == 5))
        {
            input[i] = 'm';
        }
    }
    if (count != 0)
    {
        QMessageBox::warning(this,"错误","括号不匹配");
        emit errorInput(3);
        return false;
    }

    if (mode == 3)
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == QChar(0x220F)) // 连乘
            {
                initialinput = input;
                input.remove(i, 1);
                if (input[i] != 'M')
                {
                    input.insert(i, "M");
                }
                break;
            }
        }
        // 判断输入是否合法(是否有'=')
        bool flag = false;
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '=')
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            QMessageBox::warning(this,"错误","输入有误");
            emit errorInput(4);
            return false;
        }
        if (!(input[0] >= 'A' && input[0] <= 'Z' && input[1] == '(')) // 判断输入是否合法
        {
            QMessageBox::warning(this,"错误","输入有误");
            emit errorInput(5);
            return false;
        }
    }
    else if (mode == 4 || mode == 5)
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == QChar(0x2211)) // 连加
            {
                initialinput = input;
                input.remove(i, 1);
                if (input[i] != 'm')
                {
                    input.insert(i, "m");
                }
                break;
            }
        }
        // 判断输入是否合法(是否有'=')
        bool flag = false;
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '=')
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            QMessageBox::warning(this,"错误","输入有误");
            emit errorInput(6);
            return false;
        }
        if (!(input[0] >= 'A' && input[0] <= 'Z' && input[1] == '(')) // 判断输入是否合法
        {
            QMessageBox::warning(this,"错误","输入有误");
            emit errorInput(7);
            return false;
        }
    }
    else if (mode == 1)
    {
        for (int i = 0; i < input.length(); i++) // 检查是否有符号混用
        {
            if (input[i] == '`' || input[i] == QChar(0xD7) || input[i] == '+')
            {
                QMessageBox::warning(this,"错误","符号混用");
                emit errorInput(8);
                return false;
            }
            if (!(input[i] == '~' || input[i] == QChar(0x2227) || input[i] == QChar(0x2228) || input[i] == QChar(0x2192) || input[i] == QChar(0x2194) || input[i] == '(' || input[i] == ')' || input[i] == QChar(0x2295) || input[i] == QChar(0x2191) || input[i] == QChar(0x2193) || (input[i] >= 'A' && input[i] <= 'Z')))
            {
                QMessageBox::warning(this,"错误","输入有误");
                emit errorInput(9);
                return false;
            }
        }
        initialinput = input; // 保存初始输入
    }
    else if (mode == 2)
    {
        for (int i = 0; i < input.length(); i++) // 检查是否有符号混用
        {
            if (input[i] == '~' || input[i] == QChar(0x2227) || input[i] == QChar(0x2228))
            {
                QMessageBox::warning(this,"错误","符号混用");
                emit errorInput(10);
                return false;
            }
            if ((i == 0 && input[i] == '`') || (input[i] == '`' && (!(input[i-1] >= 'A' && input[i-1] <= 'Z')) && input[i-1] != ')'))
            {
                QMessageBox::warning(this,"错误","输入有误");
                emit errorInput(11);
                return false;
            }
            if (!(input[i] == '`' || input[i] == QChar(0xD7) || input[i] == '+' || input[i] == QChar(0x2192) || input[i] == QChar(0x2194) || input[i] == '(' || input[i] == ')' || input[i] == QChar(0x2295) || input[i] == QChar(0x2191) || input[i] == QChar(0x2193) || (input[i] >= 'A' && input[i] <= 'Z')))
            {
                QMessageBox::warning(this,"错误","输入有误");
                emit errorInput(12);
                return false;
            }
        }
        initialinput = input; // 保存初始输入
    }
    return true;
}

void MainWidget::inputProcess()
{
    if (mode == 1 || mode == 2)
    {
        // 在头尾添加括号
        input.insert(0, "(");
        input.insert(input.length(), ")");
    }
    else // 连乘或连加式
    {
        input.remove(0, 1); // 删除函数符号
    }
}

void MainWidget::FindArg()
{
    QHash<QChar, bool> If_in_Arg; // 记录命题变元是否在ArgName中

    if (mode == 1 || mode == 2)
    {
        for (int i = 0; i < input.length(); i++)
        {
            // 跳过符号
            if (input[i] >= 'A' && input[i] <= 'Z')
            {
                if (If_in_Arg[input[i]] == false)
                {
                    ArgName.append(input[i]);
                    Argnum++;
                    If_in_Arg[input[i]] = true;
                }
            }
        }
    }
    else // 连乘或连加式
    {
        int i = 1;
        for (; input[i] != ')'; i++)
        {
            if (input[i] == '=')
            {
                QMessageBox::warning(this,"错误","输入有误");
                emit errorInput(13);
                return;
            }
            if (input[i] == 'v')
            {
                input[i] = 'V';
            }
            if (input[i] >= 'A' && input[i] <= 'Z')
            {
                if (If_in_Arg[input[i]] == false)
                {
                    ArgName.append(input[i]);
                    Argnum++;
                    If_in_Arg[input[i]] = true;
                }
            }
        }
        if (input[i+1] != '=')
        {
            QMessageBox::warning(this,"错误","输入有误");
            emit errorInput(14);
            return;
        }
        input.remove(0, i+2); // 删除如(a,B,c,d)= 的部分
        if (input[0] == QChar(0x2211))
        {
            input.remove(0,1);
        }
    }

    // 按字母顺序重排
    for (int i = 0; i < Argnum; i++)
    {
        for (int j = i + 1; j < Argnum; j++)
        {
            if (ArgName[i] > ArgName[j])
            {
                QChar temp = ArgName[i];
                ArgName[i] = ArgName[j];
                ArgName[j] = temp;
            }
        }
    }
}

void MainWidget::BuildHashTable()
{
    ToBin.clear();
    ToDec.clear();
    for (int i = 0; i < pow(2,Argnum); i++)
    {
        QString binstr;
        for (int j = 0; j < Argnum; j++)
        {
            binstr += (i >> j) & 1 ? '1' : '0'; // 将十进制数转换为二进制数
        }
        // 反转字符串
        for (int j = 0; j < binstr.length() / 2; j++)
        {
            QChar temp = binstr[j];
            binstr[j] = binstr[binstr.length() - j - 1];
            binstr[binstr.length() - j - 1] = temp;
        }
        ToBin[i] = binstr;
        ToDec[binstr] = i;
        If_unrelated[i] = false; // 初始化无关项
    }
}

void MainWidget::resetLineEdit()
{
    qDebug() << "text changed";
    if (initialinput.size() != 0)
    {
        InitAll();
        ui->textEdit->setText("");
        ui->lineEdit->setStyleSheet("background-color: white;");
        disconnect(ui->lineEdit, &QLineEdit::selectionChanged, this, MainWidget::resetLineEdit);
        disconnect(ui->lineEdit,&QLineEdit::textChanged,this,MainWidget::resetLineEdit);
        return;
    }
}

void MainWidget::on_clearButton_clicked()
{
    resetLineEdit();
    ui->lineEdit->setText("");
}

void MainWidget::on_delButton_clicked()
{
    resetLineEdit();
    input = ui->lineEdit->text();
    input.chop(1);
    ui->lineEdit->setText(input);
}

void MainWidget::on_truthtableButton_clicked()
{
    if (initialinput.size()==0)
    {
        on_commitButton_clicked();
    }
    if (maketruthtable == NULL)
    {
        this->maketruthtable = new MakeTruthTable;
        this->maketruthtable->generateTruthTable(ArgName,initialinput,ToBin,Value,If_unrelated);
    }
    this->maketruthtable->show();
}

void MainWidget::on_cnfButton_clicked()
{
    if (initialinput.size()==0)
    {
        on_commitButton_clicked();
    }
    QString NFresult;
    if (Argnum == 1)
    {
        NFresult = "只有一个变元,不计算范式";
    }
    else
    {
        if (NF.empty())
        {
            paradigms = new Paradigms;
            paradigms->Set(ArgName,ToBin,Value,mode);
            NF = paradigms->NF();
            if (NF.empty())
            {
                emit errorInput(15);
                return;
            }
        }
        NFresult += "主合取范式：\n" + NF[0] + '\n' + NF[2] + '\n';
    }

    QString nowtext = ui->textEdit->toPlainText();
    ui->textEdit->setText(nowtext + '\n' + NFresult);
}

void MainWidget::on_dnfButton_clicked()
{
    if (initialinput.size()==0)
    {
        on_commitButton_clicked();
    }
    QString NFresult;
    if (Argnum == 1)
    {
        NFresult = "只有一个变元,不计算范式";
    }
    else
    {
        if (NF.empty())
        {
            paradigms = new Paradigms;
            paradigms->Set(ArgName,ToBin,Value,mode);
            NF = paradigms->NF();
            if (NF.empty())
            {
                emit errorInput(15);
                return;
            }
        }
        NFresult += "主析取范式：\n" + NF[1] + '\n' + NF[3] + '\n';
    }

    QString nowtext = ui->textEdit->toPlainText();
    ui->textEdit->setText(nowtext + '\n' + NFresult);
}

void MainWidget::on_kmapButton_clicked()
{
    if (initialinput.size()==0)
    {
        on_commitButton_clicked();
    }
    if (kmap == NULL)
    {
        this->kmap = new Kmap;
        this->kmap->generateKmap(ArgName,Value,If_unrelated);
    }
    this->kmap->show();
}

void MainWidget::on_simplifyButton_clicked()
{
    if (initialinput.size()==0)
    {
        on_commitButton_clicked();
    }
    if (Argnum == 1)
    {
        kanuo = "只有一个变元,无需化简";
    }
    if (kanuo.size() == 0)
    {
        this->calkanuo = new Calkanuo;
        this->calkanuo->Set(ArgName,ToBin,Value,mode);
        kanuo = this->calkanuo->QM();
    }

    QString nowtext = ui->textEdit->toPlainText();
    ui->textEdit->setText(nowtext + '\n' + "卡诺图化简结果:" + kanuo + '\n');
}

void MainWidget::getTableinput(QString trans_input)
{
    qDebug() << "trans_input get";
    InitAll();
    this->input = trans_input;
    this->initialinput = trans_input;
    ui->lineEdit->setText(input);
    int i = 0;
    for (; i < input.size(); i++)
    {
        if (input[i] == QChar(0x2211))
        {
            mode = 4;
            break;
        }
    }
    for (; i < input.size(); i++)
    {
        if (input[i] == QChar(0x2211))
        {
            mode = 5;
            break;
        }
    }

    inputProcess();
    FindArg(); // 获取命题变元名
    BuildHashTable();

    calculate = new Calculate;
    calculate->Set(input,ArgName,ToBin,mode,unrelatedItems,If_unrelated);
    Value = calculate->Cal();
    If_unrelated = calculate->getUnrelated();
    delete calculate;
    if (Value.empty())
    {
        emit errorInput(18);
        return;
    }

    ui->lineEdit->setStyleSheet("background-color: #98FB98;"); // 设置背景为浅绿色

    connect(ui->lineEdit, &QLineEdit::selectionChanged, this, MainWidget::resetLineEdit);

    connect(ui->lineEdit,&QLineEdit::textChanged,this,MainWidget::resetLineEdit);
}

void MainWidget::on_shortcartButton_clicked()
{
    keybordshortcut = new KeybordShortcut;
    keybordshortcut->show();
}
