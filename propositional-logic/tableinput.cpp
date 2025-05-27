#include "tableinput.h"
#include "ui_tableinput.h"

TableInput::TableInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableInput)
{
    ui->setupUi(this);

    ArgName.clear();
    Argnum = 0;
    Value.clear();
    unrelatedItems.clear();
    If_unrelated.clear();
    now_column = 0;
    now_row = 0;

    setWindowTitle("真值表输入");

    ui->tableWidget->setEditTriggers(QTableWidget::AllEditTriggers);

    ui->label_2->setVisible(false);
    ui->label_2->setDisabled(true);
    ui->tableWidget->setVisible(false);
    ui->tableWidget->setDisabled(true);

    connect(ui->lineEdit,&QLineEdit::returnPressed,this,&TableInput::on_commitButton_clicked);

}

TableInput::~TableInput()
{
    delete ui;
}

void TableInput::receiveKey(QString keyname)
{
    if (now_column != 0 && now_column == Argnum+1)
    {
        QString value;
        if (keyname == "key_1")
            value = '1';
        else if (keyname == "key_0")
            value = '0';
        else if (keyname == "key_dash")
            value = '-';
        else
            return;

        QTableWidgetItem *item = new QTableWidgetItem(value);
        item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
        ui->tableWidget->setItem(now_row,now_column,item);

        if (value == "1" || value == "0")
        {
            if (If_unrelated[now_row] == true)
            {
                If_unrelated[now_row] = false;
                for (int i = 0; i < unrelatedItems.size(); i++)
                {
                    if (unrelatedItems[i] == now_row)
                    {
                        unrelatedItems.remove(i,1);
                        break;
                    }
                }
            }
            Value[now_row] = value.toInt();
        }
        else if (value == "-")
        {
            if (If_unrelated[now_row] == false)
            {
                unrelatedItems.append(now_row);
                If_unrelated[now_row] = true;
            }
        }
        else
        {
            if (If_unrelated[now_row] == true)
            {
                If_unrelated[now_row] = false;
                for (int i = 0; i < unrelatedItems.size(); i++)
                {
                    if (unrelatedItems[i] == now_row)
                    {
                        unrelatedItems.remove(i,1);
                        break;
                    }
                }
            }
            Value[now_row] = 0;
        }
    }
}

void TableInput::onCurrentItemChanged(QTableWidgetItem* currentItem, QTableWidgetItem* previousItem)
{
    if (currentItem != nullptr && currentItem != previousItem)
    {
        this->now_row = currentItem->row();
        this->now_column = currentItem->column();

        qDebug() << "Current Cell Position: Row" << now_row << "Column" << now_column;
    }
}

void TableInput::nextItem()
{
    qDebug() << now_column << "==" << Argnum + 1 << now_row << "next Item";
    if (now_column == Argnum + 1)
    {
        if (now_row != pow(2, Argnum) - 1)
            ui->tableWidget->setCurrentCell(now_row + 1, Argnum + 1);
        else
            ui->tableWidget->setCurrentCell(0, Argnum + 1);
    }
    else
    {
        ui->tableWidget->setCurrentCell(now_row, Argnum + 1);
    }
}

void TableInput::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
    else if (k->modifiers() == Qt::ControlModifier)
    {
        if (k->key() == Qt::Key_S)
        {
            on_symbolButton_clicked();
        }
        else if (k->key() == Qt::Key_Return)
        {
            on_finishButton_clicked();
        }
    }
    else if (k->key() == Qt::Key_Return)
    {
        emit enterPressed();
        qDebug() << "enter pressed";
    }
}

void TableInput::on_commitButton_clicked()
{
    QString input = ui->lineEdit->text();

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ' || input[i] == ',') // 去除空格和逗号
        {
            input.remove(i, 1);
            i--;
        }
        if (input[i] >= 'a' && input[i] <= 'z') // 将小写字母转换为大写字母
        {
            input[i] = input[i].toUpper();
        }
        if (!(input[i] >= 'A' && input[i] <= 'Z')) // 判断是否为命题变元
        {
            QMessageBox::warning(this,"错误","输入有误");
            return;
        }
    }
    if (input.size() == 0) // 判断输入是否为空
    {
        QMessageBox::warning(this,"错误","输入为空");
        return;
    }

    QHash<QChar, bool> If_in_Arg; // 记录命题变元是否在ArgName中
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

    ToBin.clear();
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
        Value.append(0); // 默认为0
    }

    tableinputStart();
}

void TableInput::tableinputStart()
{
    // 清空表格
    ui->tableWidget->clear();

    disconnect(ui->lineEdit,&QLineEdit::returnPressed,this,&TableInput::on_commitButton_clicked);
    connect(this,&TableInput::enterPressed,this,&TableInput::nextItem);

    // 设置表格的行数和列数
    int rowCount = pow(2, Argnum); // 行数
    int colCount = Argnum + 2; // 列数（参数列 + 结果列）
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(colCount);

    // 设置默认字体大小
    QFont font;
    font.setPointSize(14); // 设置字体大小为14
    ui->tableWidget->setFont(font);

    ui->tableWidget->setMinimumSize(500, 600);

    ui->tableWidget->setAlternatingRowColors(true);

    // 设置列标题
    QStringList headerLabels;
    headerLabels.append("序号");
    for (const QChar& ch : ArgName)
    {
        headerLabels.append(QString(ch));
    }
    headerLabels.append("预期输出的真值"); // 添加最后一列的标题
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // 设置所有列的宽度
    ui->tableWidget->setColumnWidth(0, 100);
    for (int j = 0; j < colCount-1; j++)
    {
        ui->tableWidget->setColumnWidth(j, 80); // 设置每列的宽度为80
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(colCount-1,QHeaderView::Stretch);

    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // 设置所有行的高度
    for (int i = 0; i < pow(2,Argnum); ++i)
    {
        ui->tableWidget->setRowHeight(i, 60); // 设置每行的高度为60
    }

    ui->tableWidget->verticalHeader()->setVisible(false);

    // 填充表格数据
    for (int i = 0; i < pow(2,Argnum); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 0, item);

        QString binstr = ToBin.value(i, ""); // 获取二进制数，如果不存在则返回空字符串
        for (int j = 0; j < Argnum; j++)
        {
            // 创建并设置单元格内容
            QTableWidgetItem* item = new QTableWidgetItem(QString(binstr[j]));
            item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(i, j+1, item);
        }

        QTableWidgetItem* resultItem = new QTableWidgetItem("");
        resultItem->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
        ui->tableWidget->setItem(i, colCount - 1, resultItem); // 设置结果列
    }

    ui->verticalSpacer->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

    ui->label_2->setVisible(true);
    ui->label_2->setDisabled(false);
    ui->tableWidget->setVisible(true);
    ui->tableWidget->setDisabled(false);

    connect(ui->tableWidget,&QTableWidget::cellChanged,this,&TableInput::onCellChanged);
    connect(ui->tableWidget, &QTableWidget::currentItemChanged, this, &TableInput::onCurrentItemChanged);
}

void TableInput::onCellChanged(int row, int column)
{
    QString value = ui->tableWidget->item(row, column) ? ui->tableWidget->item(row, column)->text() : "";
    qDebug() << "Cell" << row << column << "changed to" << value;

    int i = 0;
    for (; i < value.size(); i++)
    {
        if (value[i] == ' ')
        {
            value.remove(i, 1);
            i--;
        }
    }

    if (value == "1" || value == "0")
    {
        if (If_unrelated[row] == true)
        {
            If_unrelated[row] = false;
            for (int i = 0; i < unrelatedItems.size(); i++)
            {
                if (unrelatedItems[i] == row)
                {
                    unrelatedItems.remove(i,1);
                    break;
                }
            }
        }
        Value[row] = value.toInt();
    }
    else if (value == "-")
    {
        if (If_unrelated[row] == false)
        {
            unrelatedItems.append(row);
            If_unrelated[row] = true;
        }
    }
    else if (value == "")
    {
        if (If_unrelated[row] == true)
        {
            If_unrelated[row] = false;
            for (int i = 0; i < unrelatedItems.size(); i++)
            {
                if (unrelatedItems[i] == row)
                {
                    unrelatedItems.remove(i,1);
                    break;
                }
            }
        }
        Value[row] = 0;
    }
    else
    {
        QTableWidgetItem *item = new QTableWidgetItem("");
        item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
        ui->tableWidget->setItem(row,column,item);
    }
}

void TableInput::on_finishButton_clicked()
{
    disconnect(ui->tableWidget,&QTableWidget::cellChanged,this,&TableInput::onCellChanged);
    disconnect(ui->tableWidget, &QTableWidget::currentItemChanged, this, &TableInput::onCurrentItemChanged);
    disconnect(this->symbol,&Symbol::sentkey,this,&TableInput::receiveKey);
    disconnect(this,&TableInput::enterPressed,this,&TableInput::nextItem);

    trans_input = "F(";
    for (int i = 0; i < Argnum; i++)
    {
        trans_input += ArgName[i];
        trans_input += ",";
    }
    trans_input.remove(trans_input.length() - 1, 1);
    trans_input += ")=∑m(";

    for (int i = 0; i < pow(2,Argnum); i++)
    {
        if (If_unrelated[i] == false && Value[i] == 1)
        {
            trans_input += QString::number(i);
            trans_input += ",";
        }
    }
    trans_input.remove(trans_input.length() - 1, 1);
    trans_input += ")";
    if (unrelatedItems.size() != 0)
    {
        trans_input += "+∑D(";
        for (int i = 0; i < unrelatedItems.size(); i++)
        {
            trans_input += QString::number(unrelatedItems[i]);
            trans_input += ",";
        }
        trans_input.remove(trans_input.length() - 1, 1);
        trans_input += ")";
    }

    emit sentinput(trans_input);
    qDebug() << "trans_input sent";
    this->close();
}

void TableInput::on_symbolButton_clicked()
{
    symbol = new Symbol;
    symbol->show();
    connect(ui->tableWidget, &QTableWidget::currentItemChanged, this, &TableInput::onCurrentItemChanged);
    connect(this->symbol,&Symbol::sentkey,this,&TableInput::receiveKey);
}
