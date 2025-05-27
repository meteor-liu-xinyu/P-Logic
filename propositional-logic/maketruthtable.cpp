#include "maketruthtable.h"

MakeTruthTable::MakeTruthTable(QWidget *parent) :
    QWidget(parent)
{
    // 设置窗口标题
    setWindowTitle("真值表");

    tableWidget = new QTableWidget;

    // 创建主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableWidget);

    // 设置布局
    setLayout(mainLayout);

    // 设置窗口大小（可选）
    resize(800, 600);
}

MakeTruthTable::~MakeTruthTable()
{
    // 清理资源（如果需要）
}

void MakeTruthTable::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void MakeTruthTable::generateTruthTable(const QVector<QChar> &ArgName, const QString& initialinput,
                                       const QHash<int, QString>& ToBin, const QVector<int>& Value,
                                       const QHash<int, bool>& If_unrelated)
{
    int Argnum = ArgName.size(); // 命题变元个数

    // 清空表格
    tableWidget->clear();

    // 设置表格的行数和列数
    int powArgnum = static_cast<int>(pow(2, Argnum)); // 行数
    int colCount = Argnum + 2; // 列数（参数列 + 结果列）
    tableWidget->setRowCount(powArgnum);
    tableWidget->setColumnCount(colCount);

    // 设置默认字体大小
    QFont font;
    font.setPointSize(14); // 设置字体大小为14
    tableWidget->setFont(font);

    tableWidget->setAlternatingRowColors(true);

    // 设置列标题
    QStringList headerLabels;
    headerLabels.append("序号");
    for (const QChar& ch : ArgName)
    {
        headerLabels.append(QString(ch));
    }
    headerLabels.append(initialinput); // 添加最后一列的标题
    tableWidget->horizontalHeader()->setFont(font);
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // 设置所有列的宽度
    tableWidget->setColumnWidth(0, 100);
    for (int j = 1; j < colCount-1; j++)
    {
        tableWidget->setColumnWidth(j, 80); // 设置每列的宽度为80
    }
    tableWidget->horizontalHeader()->setSectionResizeMode(colCount-1,QHeaderView::Stretch);

    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // 设置所有行的高度
    for (int i = 0; i < powArgnum; ++i)
    {
        tableWidget->setRowHeight(i, 60); // 设置每行的高度为60
    }

    tableWidget->verticalHeader()->setVisible(false);

    // 填充表格数据
    for (int i = 0; i < powArgnum; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(i, 0, item);

        QString binstr = ToBin.value(i, ""); // 获取二进制数，如果不存在则返回空字符串
        for (int j = 0; j < Argnum; j++)
        {
            // 创建并设置单元格内容
            QTableWidgetItem* item = new QTableWidgetItem(QString(binstr[j]));
            item->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(i, j+1, item);
        }

        QString result;
        // 检查 If_unrelated 是否包含 i 键，如果不包含则默认为 false
        bool isUnrelated = If_unrelated.contains(i) ? If_unrelated.value(i) : false;
        if (isUnrelated)
        {
            result = "?=" + QString::number(Value[i]);
        }
        else
        {
            result = QString::number(Value[i]);
        }
        QTableWidgetItem* resultItem = new QTableWidgetItem(result);
        resultItem->setTextAlignment(Qt::AlignCenter); // 设置居中对齐
        resultItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(i, colCount - 1, resultItem); // 设置结果列
    }
}

