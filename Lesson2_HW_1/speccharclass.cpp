#include "speccharclass.h"

SpecCharClass::SpecCharClass()
{
    variants["#@CR@"] = QString("©");
    variants["#@PM@"] = QString("‰");
    variants["#@EURO@"] = QString("€");
    variants["#@RUB@"] = QString("₽");
}

QString SpecCharClass::replace(QString text) const
{
  for (auto iter = variants.constBegin(); iter != variants.constEnd(); iter++)
  {
      text.replace(iter.key(), iter.value());
  }
  return text;

//            for (auto iter = variants.constBegin(); iter != variants.constEnd(); iter++)
//            {
//                text.replace(iter.key(), iter.value());
//            }



}
