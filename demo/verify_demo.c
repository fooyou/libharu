
/*
 * << Haru Free PDF Library 2.0.0 >> -- converter_demo.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <time.h>
#include "hpdf.h"

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
            (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

int main (int argc, char **argv)
{
    clock_t start, finish;
    double duration;
    const wchar_t *HELLO =
            L"Hello.\x09 \uFFF9مرحبا.\u200F\uFFFAmarḥába\uFFFB สวัสดี\x0A नमस्कार.\x0C "
                    L"שלום.\u200F 안녕하세요．\x0D\uFFF9你好\uFFFAnǐhǎo\uFFFB。こんにちは。"
    ;
    const wchar_t *HELLO_ru =
            L"Здравствуйте. "
    ;
    const wchar_t *  CN_STR =
        L"电话：\n"
                "韩国\n"
                "中国\n"
                "传真\n"
                "网站：\n"
                "信息\n"
                "平台：\n"
                "模块：\n"
                "序列号：\n"
                "版本：\n"
                "文件浏览\n"
                "路径：\n"
                "文件名\n"
                "日期\n"
                "文件操作\n"
                "删除\n"
                "复制\n"
                "重命名\n"
                "新建文件夹\n"
                "文件类型\n"
                "打开\n"
                "操作\n"
                "待机和亮度\n"
                "背光亮度\n"
                "电池\n"
                "待机时间\n"
                "关闭\n"
                "自动关闭\n"
                "适配器\n"
                "声音\n"
                "测量提示音\n"
                "按键提示音\n"
                "关闭声音\n"
                "时间\n"
                "时/分/秒：\n"
                "应用\n"
                "语言\n"
                "升级\n"
                "系统维护\n"
                "软件升级\n"
                "恢复出厂设置\n"
                "确认\n"
                "皮肤设置\n"
                "点击升级按钮开始升级\n"
                "确认电量50%以上升级！\n"
                "确定\n"
                "取消\n"
                "尝试加载SD卡和U盘......\n"
                "正在查找升级文件......\n"
                "请插入SD卡或者U盘......\n"
                "请将升级文件放入SD卡或者U盘根目录下！\n"
                "解压失败，请重启系统后再次进行升级！\n"
                "正在解压升级文件......\n"
                "升级包损坏！\n"
                "升级失败，请重启系统后再次进行升级！\n"
                "升级成功，请重启系统！\n"
                "当前升级文件不适用于本系统，请更换升级文件！\n"
                "确认要升级到低版本吗？\n"
                "正在写入扇区......\n"
                "打开WLAN\n"
                "打开WLAN查看可用网络\n"
                "正在打开WIFI……\n"
                "初始化WIFI失败\n"
                "正在关闭WIFI……\n"
                "已连接的WLAN\n"
                "选取附近的WLAN\n"
                "WLAN设置\n"
                "正在进行身份认证\n"
                "WiFi初始化成功！"
    ;

    const wchar_t *  ARABIA_STR =
            L"تلفن:\n"
                    "کره\n"
                    "چین\n"
                    "نمابر\n"
                    "سایت :\n"
                    "اطلاعات\n"
                    "پلت فرم :\n"
                    "ماژول :\n"
                    "شماره سریال :\n"
                    "شماره نگارش :\n"
                    "انتخاب فایل\n"
                    "مسیر :\n"
                    "نام فایل\n"
                    "تاریخ\n"
                    "عملیات فایل\n"
                    "حذف\n"
                    "کپی\n"
                    "تغییر نام\n"
                    "ساخت پوشه\n"
                    "نوع فایل\n"
                    "بازکردن\n"
                    "عملکرد\n"
                    "انرژی\n"
                    "نور پس زمینه\n"
                    "باتری\n"
                    "زمان آماده به کار\n"
                    "خاموش\n"
                    "خاموشی خودکار\n"
                    "آداپتور\n"
                    "صدا\n"
                    "عملیات\n"
                    " کلیدها\n"
                    "خاموش\n"
                    "زمان\n"
                    "ساعت/دقیقه/ثانیه:\n"
                    "اجرا\n"
                    "زبان\n"
                    "ارتقاء\n"
                    "نگهداری سیستم\n"
                    "ارتقاء نرم افزار\n"
                    "برگشت به تنظیمات کارخانه\n"
                    "تایید\n"
                    "پوسته\n"
                    "برای شروع کلید ارتقاء را فشار دهید\n"
                    "ظرفیت باتری باید بیشتر از 50 درصد باشد\n"
                    "تایید\n"
                    "لغو\n"
                    "تلاش برای بارگذاری حافظه USB یا SD\n"
                    "یافتن فایل ارتقاء\n"
                    "لطفا حافظه USB یا SD را وارد کنید\n"
                    "لطفا فایل ارتقاء را در مسیر ریشه حافظه USB یا SD قرار دهید\n"
                    "خطا در بازکردن فایل ارتقاء ، سیستم را دوباره راه اندازی کنید \n"
                    "بازکردن فایل ارتقاء ......\n"
                    "فایل ارتقاء آسیب دیده است!\n"
                    "عملیات ارتقاء انجام نشد، دستگاه را مجدد راه اندازی کنید\n"
                    "عملیات ارتقاء موفق بود،دستگاه را مجدد راه اندازی کنید\n"
                    "فایل ارتقاء فعلی روی دستگاه نصب نمی شود، لطفا از فایل دیگری استفاده کنید!\n"
                    "ارتقاء به نسخه قدیمی تر را تایید می کنید؟\n"
                    "نوشتن رو حافظه\n"
                    " روشن کردن شبکه بیسیم\n"
                    "برای اتصال به شبکه ، شبکه بیسیم را روشن کنید\n"
                    "روشن کردن WIFI\n"
                    "خطا در اتصال به WIFI\n"
                    "خاموش کردن WIFI\n"
                    "متصل شد\n"
                    "انتخاب شبکه در دسترس\n"
                    "تنظیمات شبکه بیسیم\n"
                    "بررسی احراز هویت\n"
                    "موفقیت در مقداردهی اولیه WIFI.";

    const wchar_t * SPANISH_STR =
            L"TEL:\n"
                    "Corea\n"
                    "China\n"
                    "Fax\n"
                    "Sitio web\n"
                    "Información\n"
                    "Plataforma:\n"
                    "Módulo:\n"
                    "Nº serie:\n"
                    "Versión:\n"
                    "Buscar archivo\n"
                    "Ruta:\n"
                    "Nombre de archivo\n"
                    "Fecha\n"
                    "Operación de archivo\n"
                    "Eliminar\n"
                    "Copiar\n"
                    "Nuevo nombre\n"
                    "Crear carpeta\n"
                    "Tipo de archivo\n"
                    "Abrir\n"
                    "Operar\n"
                    "Modo de energía\n"
                    "Brillo de luz de fondo\n"
                    "Batería\n"
                    "Tiempo espera\n"
                    "Apagar\n"
                    "Autoapagado\n"
                    "Adaptador\n"
                    "Sonido\n"
                    "Operación \n"
                    "Teclado\n"
                    "Apagar sonido\n"
                    "Tiempo\n"
                    "H/M/S\n"
                    "Aplicar\n"
                    "Idioma\n"
                    "Actualizar\n"
                    "Mantenimiento de sistema\n"
                    "Actualizar software\n"
                    "Inicialización de fábrica\n"
                    "Confirmar\n"
                    "Forro\n"
                    "Presione botón de actualización para iniciar\n"
                    "Antes de iniciar el proceso de mejora， asegúrese de que su batería está por encima del 50 %\n"
                    "Confirmar\n"
                    "Cancelar\n"
                    "Tratando de cargar USB o tarjeta SD...\n"
                    "Buscando archivo de actualización...\n"
                    "Inserte USB o tarjeta SD\n"
                    "Guarde el archivo de mejora en una tarjeta SD o en el directorio raíz de un USB\n"
                    "Fallado descomprimir. Reinice el sistema y actualice otra vez.\n"
                    "Descomprimiendo archivo de actualización...\n"
                    "El parche de actualización fue dañado!\n"
                    "Fallado actualizar， actualice otra vez y reinicie el sistema!\n"
                    "Logrado actualizar， reinicie el sistema!\n"
                    "No se puede aplicar el archivo de actualización al sistema. Cambie el archivo de actualización!\n"
                    "Desea degradar?\n"
                    "Escribiendo en sector...\n"
                    "Prender WLAN\n"
                    "Prenda WLAN para verificar estado de red\n"
                    "Prender WIFI\n"
                    "Fallado inicializar WIFI\n"
                    "Apagar WIFI\n"
                    "Conectado\n"
                    "Seleccionar WLAN cercano\n"
                    "Config.WLAN\n"
                    "Verifique la autentificación de la identidad\n"
                    "Logrado inicializar WIFI"
    ;

    const wchar_t * PERSIAN_STR =
            L"تلفن:\n"
                    "کره\n"
                    "چین\n"
                    "نمابر\n"
                    "سایت :\n"
                    "اطلاعات\n"
                    "پلت فرم :\n"
                    "ماژول :\n"
                    "شماره سریال :\n"
                    "شماره نگارش :\n"
                    "انتخاب فایل\n"
                    "مسیر :\n"
                    "نام فایل\n"
                    "تاریخ\n"
                    "عملیات فایل\n"
                    "حذف\n"
                    "کپی\n"
                    "تغییر نام\n"
                    "ساخت پوشه\n"
                    "نوع فایل\n"
                    "بازکردن\n"
                    "عملکرد\n"
                    "انرژی\n"
                    "نور پس زمینه\n"
                    "باتری\n"
                    "آماده به کار\n"
                    "خاموش\n"
                    "خاموشی خودکار\n"
                    "آداپتور\n"
                    "صدا\n"
                    "عملیات\n"
                    "کلیدها\n"
                    "خاموش\n"
                    "زمان\n"
                    "ساعت/دقیقه/ثانیه:\n"
                    "اجرا\n"
                    "زبان\n"
                    "ارتقاء\n"
                    "نگهداری سیستم\n"
                    "ارتقاء نرم افزار\n"
                    "برگشت به تنظیمات کارخانه\n"
                    "تایید\n"
                    "پوسته\n"
                    " کلید ارتقاء را فشار دهید\n"
                    "ظرفیت باتری باید بیشتر از 50 درصد باشد\n"
                    "تایید\n"
                    "لغو\n"
                    "تلاش برای بارگذاری حافظه USB یا SD\n"
                    "یافتن فایل ارتقاء\n"
                    "لطفا حافظه USB یا SD را وارد کنید\n"
                    "لطفا فایل ارتقاء را در مسیر ریشه حافظه USB یا SD قرار دهید\n"
                    "خطا در بازکردن فایل ارتقاء ، سیستم را دوباره راه اندازی کنید\n"
                    "بازکردن فایل ارتقاء ......\n"
                    "فایل ارتقاء آسیب دیده است!\n"
                    "عملیات ارتقاء انجام نشد، دستگاه را مجدد راه اندازی کنید\n"
                    "ارتقاء انجام شد ، دستگاه را مجدد راه اندازی کنید\n"
                    "فایل ارتقاء فعلی روی دستگاه نصب نمی شود، لطفا از فایل دیگری استفاده کنید!\n"
                    "نصب نسخه قدیمی تر را تایید می کنید؟\n"
                    "نوشتن رو حافظه\n"
                    "روشن کردن شبکه بیسیم\n"
                    "برای اتصال به شبکه ، شبکه بیسیم را روشن کنید\n"
                    "روشن کردن WIFI\n"
                    "خطا در اتصال به WIFI\n"
                    "خاموش کردن WIFI\n"
                    "متصل شد\n"
                    "انتخاب شبکه در دسترس\n"
                    "تنظیمات شبکه بیسیم\n"
                    "بررسی احراز هویت\n"
                    "موفقیت در مقداردهی اولیه WIFI."
    ;

    HPDF_Doc  pdf;
    char fname[256];
    HPDF_Page page;
    HPDF_Font detail_font, detail_font_v, relief_font;
    const char *detail_font_name;
    HPDF_REAL page_width, page_height;
    HPDF_UINT len;
    HPDF_Rect rect;
    HPDF_INT ttopt;

    if (2 < argc || (1 < argc &&
                     (argv[1][0] != '-' || argv[1][1] != 'c' || argv[1][2] != 0))) {
        printf ("usage: converter_demo [-c]\n");
        return 1;
    }

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    ttopt = HPDF_FONTOPT_EMBEDDING;
    if (1 < argc)
        ttopt |= HPDF_FONTOPT_WITHOUT_CID_MAP;

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_SetCompressionMode (pdf, HPDF_COMP_IMAGE | HPDF_COMP_METADATA);

    HPDF_UseCNSEncodings (pdf);
    HPDF_UseCNTEncodings (pdf);
    HPDF_UseJPEncodings (pdf);
    HPDF_UseKREncodings (pdf);
    HPDF_UseUTFEncodings (pdf);

    HPDF_UseCNSFonts (pdf);
    HPDF_UseCNTFonts (pdf);
    HPDF_UseJPFonts (pdf);
    HPDF_UseKRFonts (pdf);


    /* Devanagari */
    detail_font_name = HPDF_LoadTTFontFromFile (pdf, "./ttfont/Mangal.ttf", ttopt);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF16-H");

    /* Thai, Armenian */
    detail_font_name = HPDF_LoadTTFontFromFile (pdf, "./ttfont/Tahoma.ttf", ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);
    relief_font = detail_font_v;
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF16-H");
    HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    /* Korean */
    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf, "./ttfont/gulim.ttc", 1, ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "UniKS-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Simplified Chinese, Traditional Chinese, Japanese */
    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf, "./ttfont/simsun.ttc", 1, ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "UniGB-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Latin, Cyrillic, Greek, Arabic, Hebrew */
    detail_font_name = HPDF_LoadTTFontFromFile (pdf, "./ttfont/times.ttf", ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

//    /* Armenian */
//    detail_font_name = HPDF_LoadTTFontFromFile(pdf, "./ttfont/aliku.ttf", ttopt);
//    relief_font = detail_font;
//    detail_font = HPDF_GetFont(pdf, detail_font_name, "Ancient-UTF8-H");
//    HPDF_Font_SetReliefFont (detail_font, relief_font);

    HPDF_Font_PushBuiltInConverter (detail_font, "BiDi", NULL);
    HPDF_Font_SetCharacterEncoding (detail_font, HPDF_CHARENC_WCHAR_T);


//    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf, "./ttfont/batang.ttc", 1, ttopt);
////    detail_font_name = "Batang";
//    relief_font = detail_font_v;
//    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniKS-UTF16-V");
//    HPDF_Font_SetReliefFont (detail_font_v, relief_font);
//
//    detail_font_name = HPDF_LoadTTFontFromFile (pdf, "./ttfont/simhei.ttf", ttopt);
////    detail_font_name = "SimHei";
//    relief_font = detail_font_v;
//    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniGB-UTF16-V");
//    HPDF_Font_SetReliefFont (detail_font_v, relief_font);
//
//    detail_font_name = HPDF_LoadTTFontFromFile (pdf, "./ttfont/arial.ttf", ttopt);
//    relief_font = detail_font_v;
//    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF16-H");
//    HPDF_Font_SetReliefFont (detail_font_v, relief_font);
//
//    // HPDF_Font_PushBuiltInConverter (detail_font_v, "BiDi", NULL);
//    HPDF_Font_SetCharacterEncoding (detail_font_v, HPDF_CHARENC_WCHAR_T);


    start = clock();


    /* Add a new page object. */
    page = HPDF_AddPage (pdf);

    page_width  = 595.27559F;
    page_height = 841.88976F;

    HPDF_Page_SetWidth  (page, page_width);
    HPDF_Page_SetHeight (page, page_height);

    HPDF_Page_BeginText (page);

    HPDF_Page_SetFontAndSize (page, detail_font, 15);
    HPDF_Page_SetWordSpace (page, 5);
    HPDF_Page_SetCharSpace (page, 0);

    HPDF_Page_SetTextLeading (page, 0);
    HPDF_Page_SetJustifyRatio (page, 1, 1, 100);

    HPDF_Page_TextRect (page,
                        30,
                        page_height - 60,
                        page_width / 4 - 29,
                        30,
                        (const char *)  CN_STR,
                        HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY_ALL |
                        HPDF_ALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_ALIGNOPT_REMOVE_TATWEEL,
                        &len);

    HPDF_Page_TextRect (page,
                        30 + page_width / 4 - 29,
                        page_height - 60,
                        page_width - 30 - 2 * (30 + page_width / 4 - 29),
                        30,
                        (const char *)  ARABIA_STR,
                        HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY_ALL |
                        HPDF_ALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_ALIGNOPT_REMOVE_TATWEEL,
                        &len);


    HPDF_Page_TextRect (page,
                        30 + 2 * (page_width / 4 - 29),
                        page_height - 60,
                        page_width - 30 - (30 + page_width / 4 - 29),
                        30,
                        (const char *)  SPANISH_STR,
                        HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY_ALL |
                        HPDF_ALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_ALIGNOPT_REMOVE_TATWEEL,
                        &len);

    HPDF_Page_TextRect (page,
                        30 + 3 * (page_width / 4 - 29),
                        page_height - 60,
                        page_width - 30,
                        30,
                        (const char *)  PERSIAN_STR,
                        HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY_ALL |
                        HPDF_ALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_ALIGNOPT_REMOVE_TATWEEL,
                        &len);

    /* Finish to print text. */
    HPDF_Page_EndText (page);


//    HPDF_Page_SetLineWidth (page, 0.5);
//
//    HPDF_Page_MoveTo (page, 10, page_height - 25);
//    HPDF_Page_LineTo (page, page_width - 10, page_height - 25);
//    HPDF_Page_Stroke (page);
//
//    HPDF_Page_Rectangle (page, 30, page_height - 60,
//                         page_width / 2 - 29 - 30, 30 - (page_height - 60));
//    HPDF_Page_Stroke (page);
//
//    HPDF_Page_Rectangle (page, page_width / 2 + 40, page_height - 60,
//                         page_width - 30 - (page_width / 2 + 40), 405 - (page_height - 60));
//    HPDF_Page_Stroke (page);
//
//    HPDF_Page_Rectangle (page, page_width / 2 + 40, 380,
//                         page_width - 30 - (page_width / 2 + 40), 30 - 380);
//    HPDF_Page_Stroke (page);


    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f seconds/n", duration);

    return 0;
}
