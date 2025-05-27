#include "kmap.h"

Kmap::Kmap(QWidget *parent) :
    QWidget(parent)
{

    // 设置窗口标题
    setWindowTitle("卡诺图");

    // 创建 QTableWidget
    tableWidget = new QTableWidget(this);

    // 创建主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableWidget);

    // 设置布局
    setLayout(mainLayout);

    // 设置窗口大小（可选）
    resize(650, 550);
}

Kmap::~Kmap()
{

}

void Kmap::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

QVector<QString> Kmap::GenerateGrayCode(int n) // 生成n位格雷码
{
    QVector<QString> grayCode;

    // 1 位格雷码
    grayCode.push_back("0");
    grayCode.push_back("1");

    // 迭代生成 n 位格雷码
    for (int i = 2; i <= n; i++)
    {
        int currentSize = grayCode.size();

        // 反映当前的 Gray code
        for (int j = currentSize - 1; j >= 0; j--)
        {
            grayCode.push_back(grayCode[j]);
        }

        // 在上半部分添加 '0'
        for (int j = 0; j < currentSize; j++)
        {
            grayCode[j] = "0" + grayCode[j];
        }

        // 在下半部分添加 '1'
        for (int j = currentSize; j < grayCode.size(); j++)
        {
            grayCode[j] = "1" + grayCode[j];
        }
    }

    return grayCode;
}

void Kmap::generateKmap(const QVector<QChar> &ArgName, const QVector<int> &Value, const QHash<int,bool> &If_unrelated)
{
    int Argnum = ArgName.size(); // 命题变元个数

    // 清空表格
    tableWidget->clear();

    if (Argnum %2 == 1) // 奇数个变元
    {
        int n = Argnum / 2 + 1;

        // 设置表格的行数和列数
        int rowCount = pow(2,n) +1; // 行数
        int colCount = pow(2,n-1) + 1; // 列数
        tableWidget->setRowCount(rowCount);
        tableWidget->setColumnCount(colCount);

        // 设置默认字体大小
        QFont font;
        font.setPointSize(14); // 设置字体大小为14
        tableWidget->setFont(font);

        tableWidget->setAlternatingRowColors(true);

        QString Args;
        for (int i = 0; i < n ; i++)
        {
            Args.append(ArgName[i]);
        }
        Args.append("\\");
        for (int i = 0; i < n-1; i++)
        {
            Args.append(ArgName[i+n]);
        }
        QVector<QString> graycode1 = GenerateGrayCode(n); // 生成n位格雷码
        QVector<QString> graycode2 = GenerateGrayCode(n-1); // 生成n-1位格雷码

        // 设置列标题
        QStringList headerLabels;
        headerLabels.append(Args);
        for (int i = 0; i < pow(2,n-1); i++)
        {
            headerLabels.append(graycode1[i]);
        }
        tableWidget->horizontalHeader()->setFont(font);
        tableWidget->setHorizontalHeaderLabels(headerLabels);

        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        // 设置所有列的宽度

        tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
        for (int j = 1; j < colCount; j++)
        {
            tableWidget->setColumnWidth(j, 100); // 设置每列的宽度为80
        }

        tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        // 设置所有行的高度
        for (int i = 0; i < rowCount; i++)
        {
            tableWidget->setRowHeight(i, 60); // 设置每行的高度为60
        }

        tableWidget->verticalHeader()->setVisible(false);

        QVector<int> num1;
        QVector<int> num2;
        for (int i = 0; i < pow(2,n); i++)
        {
            // 将第i个n位格雷码最后添加两个0后转为十进制
            int temp = 0;
            QString tempstring = graycode1[i];
            tempstring.append(QString(n - 1, '0')); // 在格雷码后添加 n-1 个 '0'
            for (int j = 0; j < tempstring.length(); j++)
            {
                temp += tempstring[j].digitValue() * pow(2,tempstring.length()-1-j);
            }
            num1.push_back(temp);
        }
        for (int i = 0; i < pow(2,n-1); i++)
        {
            // 将第i个n-1位格雷码转换为十进制数
            int temp = 0;
            for (int j = 0; j < n-1; j++)
            {
                temp += graycode2[i][j].digitValue() * pow(2,n-2-j);
            }
            num2.push_back(temp);
        }
        for (int i = 0; i < pow(2,n); i++)
        {
            // 创建并设置单元格内容
            QTableWidgetItem* item = new QTableWidgetItem(graycode1[i]);
            item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(i, 0, item);
            for (int j = 0; j < pow(2,n-1); j++)
            {
                QString itemstring;
                if (If_unrelated[num1[i]+num2[j]] == true)
                {
                    if (Value[num1[i]+num2[j]] == 1)
                    {
                        itemstring = "?=1";
                    }
                    else
                    {
                        itemstring = "?=0";
                    }
                }
                else
                {
                    if (Value[num1[i]+num2[j]] == 1)
                    {
                        itemstring = "1";
                    }
                    else
                    {
                        itemstring = "0";
                    }
                }
                // 创建并设置单元格内容
                QTableWidgetItem* item = new QTableWidgetItem(itemstring);
                item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(i, j+1, item);
            }
        }
    }
    else //Argnum % 2 == 0
    {
        int n = Argnum / 2;

        // 设置表格的行数和列数
        int rowCount = pow(2,n) +1; // 行数
        int colCount = pow(2,n) + 1; // 列数
        tableWidget->setRowCount(rowCount);
        tableWidget->setColumnCount(colCount);

        // 设置默认字体大小
        QFont font;
        font.setPointSize(14); // 设置字体大小为14
        tableWidget->setFont(font);

        tableWidget->setAlternatingRowColors(true);

        QString Args;
        for (int i = 0; i < n ; i++)
        {
            Args.append(ArgName[i]);
        }
        Args.append("\\");
        for (int i = 0; i < n; i++)
        {
            Args.append(ArgName[i+n]);
        }
        QVector<QString> graycode = GenerateGrayCode(n); // 生成n位格雷码
        // 设置列标题
        QStringList headerLabels;
        headerLabels.append(Args);
        for (int i = 0; i < pow(2,n); i++)
        {
            headerLabels.append(graycode[i]);
        }
        tableWidget->horizontalHeader()->setFont(font);
        tableWidget->setHorizontalHeaderLabels(headerLabels);

        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        // 设置所有列的宽度

        tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
        for (int j = 1; j < colCount; j++)
        {
            tableWidget->setColumnWidth(j, 80); // 设置每列的宽度为80
        }

        tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        // 设置所有行的高度
        for (int i = 0; i < rowCount; i++)
        {
            tableWidget->setRowHeight(i, 60); // 设置每行的高度为60
        }

        tableWidget->verticalHeader()->setVisible(false);

        QVector<int> num1;
        QVector<int> num2;
        for (int i = 0; i < pow(2,n); i++)
        {
            // 将第i个n位格雷码最后添加两个0后转为十进制
            int temp = 0;
            QString tempstring = graycode[i];
            tempstring.append(QString(n, '0')); // 在格雷码后添加 n-1 个 '0'
            for (int j = 0; j < tempstring.size(); j++)
            {
                temp += tempstring[j].digitValue() * pow(2,tempstring.size()-1-j);
            }
            num1.push_back(temp);
        }
        for (int i = 0; i < pow(2,n); i++)
        {
            int temp = 0;
            for (int j = 0; j < n; j++)
            {
                temp += graycode[i][j].digitValue() * pow(2,n-1-j);
            }
            num2.push_back(temp);
        }
        for (int i = 0; i < pow(2,n); i++)
        {
            // 创建并设置单元格内容
            QTableWidgetItem* item = new QTableWidgetItem(graycode[i]);
            item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(i, 0, item);
            for (int j = 0; j < pow(2,n); j++)
            {
                QString itemstring;
                if (If_unrelated[num1[i]+num2[j]] == true)
                {
                    if (Value[num1[i]+num2[j]] == 1)
                    {
                        itemstring = "?=1";
                    }
                    else
                    {
                        itemstring = "?=0";
                    }
                }
                else
                {
                    if (Value[num1[i]+num2[j]] == 1)
                    {
                        itemstring = "1";
                    }
                    else
                    {
                        itemstring = "0";
                    }
                }

                // 创建并设置单元格内容
                QTableWidgetItem* item = new QTableWidgetItem(itemstring);
                item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(i, j+1, item);
            }
        }
    }
}
