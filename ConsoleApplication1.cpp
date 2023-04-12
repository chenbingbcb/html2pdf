#include <ctemplate/template.h>
#include <string>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QTextDocument>
#include <QTextStream>
#include <QFile>
#include <QPrinter>
#include <QApplication>
#include <QTextBlock>
#include <QTextEdit>

#pragma comment(lib,"libctemplate-debug.lib")

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	// 形成数据字典
	ctemplate::TemplateDictionary dic("test");
	dic.SetValue("purchaseId", u8"SC-20230213-0959");
    dic.SetValue("projectName", u8"WQH【竞争性谈判-服务-多品目-报价上浮】230213");
    dic.SetValue("packageId", u8"1");
    dic.SetValue("bidderName", u8"测试供应商E");
    dic.SetValue("table1_note", u8"材料必须要好啊");
    dic.SetValue("table2_note", u8"房间必须打扫干净");
    dic.SetValue("bidderSign", u8"测试供应商E");
    dic.SetValue("date", u8"2023年03月03日");

    for (int i = 0; i < 6; ++i)
    {
        ctemplate::TemplateDictionary* table1_dict;
        table1_dict = dic.AddSectionDictionary("thead1");
        table1_dict->SetValue("head1", u8"标题" + std::to_string(i));
    }

    for (int i = 0; i < 100; ++i)
    {
        ctemplate::TemplateDictionary* table1_dict;
        table1_dict = dic.AddSectionDictionary("TABLE1");
        table1_dict->SetValue("field1", u8"五常大米" + std::to_string(i));
        table1_dict->SetValue("field2", "2");
        table1_dict->SetValue("field5", "10");

        // 这里有点类似于printf
        table1_dict->SetFormattedValue("field4", "%d", i);

        ctemplate::TemplateDictionary* table2_dict;
        table2_dict = dic.AddSectionDictionary("TABLE2");
        table2_dict->SetValue("field1", u8"房屋保养服务" + std::to_string(i));
        table2_dict->SetValue("field2", "2");

        // 这里有点类似于printf
        table2_dict->SetFormattedValue("field5", "%d", i);
    }

	// 构建空网页模板对象
	std::string empty_html = "./test.html";     // 空的网页模板
	ctemplate::Template* tp = ctemplate::Template::GetTemplate(empty_html, ctemplate::DO_NOT_STRIP);

	// 渲染网页模板（将网页中的变量 name 替换成 "张三"）
	std::string filled_html;
	tp->Expand(&filled_html, &dic);

	qDebug() << filled_html.c_str();


	QPrinter printer(QPrinter::HighResolution);
	printer.setPageSize(QPrinter::A4);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName("output.pdf");

    //QFile PdfFile("C:/ok.html");
    //PdfFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    //PdfFile.write(filled_html.c_str());
    ////PdfFile.open(QIODevice::ReadOnly);
    ////QByteArray ba = PdfFile.readAll();
    //PdfFile.close();

	QTextDocument document;
	document.setHtml(filled_html.c_str());
    //document.setPlainText("html");
	document.print(&printer);
	//document.end();

    //on_pushButton_clicked();

	return 0;
}

