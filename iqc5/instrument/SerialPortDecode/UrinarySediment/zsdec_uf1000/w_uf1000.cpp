#include "w_uf1000.h"
#include "uf1000_setup.h"

W_Uf1000::W_Uf1000(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("尿沉渣-UF1000");

    this->loadConfig();
}

W_Uf1000::~W_Uf1000()
{

}

void W_Uf1000::decode_old(QString data)
{
    QString ls_code;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_itemcount;
    qint32 li_startpos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    li_stx = m_sData.indexOf(QString(QChar(STX)));
    ls_code = m_sData.mid(li_stx + 1,li_etx - li_stx - 1);

    if (ls_code.mid(0,2).toUpper() == "DS")
    {
        m_bIsEnd = false;
        m_sTotal = "";
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DP")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(li_etx + 1);
    }
}

void W_Uf1000::loadConfig()
{
    BaseWindow::loadConfig();

    m_bOldMode = oldmodeCheckBox->setChecked( readSetting("UF1000/oldmode","0") == "1" );
    m_bUseDcEnd = usedcCheckBox->setChecked( readSetting("UF1000/usedcend","0") == "1" );
    m_bUseDdEnd = useddCheckBox->setChecked( readSetting("UF1000/useddend","0") == "1" );
    m_bUseDfEnd = usedfCheckBox->setChecked( readSetting("UF1000/usedfend","0") == "1" );


}

void W_Uf1000::decode(QString data)
{
    QString ls_code;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_itemcount;
    qint32 li_startpos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    if (m_bOldMode)
    {
        decode_old(data);
    }

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    li_stx = m_sData.indexOf(QString(QChar(STX)));
    ls_code = m_sData.mid(li_stx + 1, li_etx - li_stx - 1);

    if (ls_code.mid(0,2).toUpper() == "DS")
    {
        m_bIsEnd = false;
        m_sTotal = "";
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DP")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(47,2).toInt();

        for (int i = 0; i < li_itemcount; i++)
        {
            m_vItemCode.push_back(m_sData.mid(1 + 49 + 12 * i,4).toUpper());
            m_vItemValue.push_back(QString::number(m_sData.mid(1 + 49 + 4 + 12 * i, 8).toDouble()));
            m_nTotalItem++;
        }

        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DC")
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);

        if (m_bUseDcEnd)
        {
            m_bIsEnd = true;
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "DQ")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(47,2).toInt();

        for (int i = 0; i < li_itemcount; i++)
        {
            m_vItemCode.push_back(m_sData.mid(1 + 49 + 12 * i,4).toUpper());
            m_vItemValue.push_back(QString::number(m_sData.mid(1 + 49 + 4 + 12 * i, 8).toDouble()));
            m_nTotalItem++;
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "DD")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(47,2).toInt();

        for (int i = 0; i < li_itemcount; i++)
        {
            m_vItemCode.push_back(m_sData.mid(1 + 49 + 12 * i,4).toUpper());
            m_vItemValue.push_back(QString::number(m_sData.mid(1 + 49 + 4 + 12 * i, 8).toDouble()));
            m_nTotalItem++;

            if (m_vItemCode[m_nTotalItem - 1] == "0C00")
            {
                m_vItemCode.pop_back();
                m_vItemValue.pop_back();
                m_nTotalItem--;
            }

            if (m_vItemCode[m_nTotalItem - 1] == "0C01")
            {
                m_vItemCode.pop_back();
                m_vItemValue.pop_back();
                m_nTotalItem--;
            }

            if (m_vItemCode[m_nTotalItem - 1] == "0C02")
            {
                m_vItemCode.pop_back();
                m_vItemValue.pop_back();
                m_nTotalItem--;
            }


            m_sData = m_sData.mid(li_etx + 1);

            if (m_bUseDdEnd)
            {
                m_bIsEnd = true;
            }
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "DV")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(47,2).toInt();

        for (int i = 0; i < li_itemcount; i++)
        {
            m_vItemCode.push_back(m_sData.mid(1 + 49 + 12 * i,4).toUpper());
            m_vItemValue.push_back(QString::number(m_sData.mid(1 + 49 + 4 + 12 * i, 8).toDouble()));
            m_nTotalItem++;
        }

        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DF")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(47,2).toInt();

        for (int i = 0; i < li_itemcount; i++)
        {
            m_vItemCode.push_back(m_sData.mid(1 + 49 + 12 * i,4).toUpper());
            m_vItemValue.push_back(QString::number(m_sData.mid(1 + 49 + 4 + 12 * i, 8).toDouble()));
            m_nTotalItem++;
        }

        m_sData = m_sData.mid(li_etx + 1);

        if (m_bUseDfEnd)
        {
            m_bIsEnd = true;
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "D1")
    {
        if (ls_code.mid(0,5).toUpper() == "D144C")
        {
            m_bIsEnd = true;
            m_sTotal += ls_code;
            m_sData = m_sData.mid(li_etx);
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "DE")
    {
        m_bIsEnd = true;
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }

    if (m_bIsEnd)
    {
        if (m_sTotal.contains("DS"))
        {
            m_bIsQc = false;
        }
        else
        {
            if (m_sTotal.contains("D144C"))
            {
                m_bIsQc = true;
                goto label_0;
            }
        }

        li_startpos = m_sTotal.indexOf("DS");
        m_sSampleNo = m_sTotal.mid(li_startpos + 70,15);


        li_year = m_sTotal.mid(li_startpos + 48, 4).toInt();
        li_month = m_sTotal.mid(li_startpos + 52, 2).toInt();
        li_day = m_sTotal.mid(li_startpos + 54, 2).toInt();

        m_sSampleDate = getSampleDate(li_year,li_month,li_day);

        for (int i = 0; i < m_nTotalItem; i++)
        {
            if (!m_bIsQc)
            {
                sendResult(m_vItemCode[i], m_vItemValue[i]);
            }
        }

label_0:
    m_sTotal = "";
    m_nTotalItem = 0;

    }


    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }
}

void W_Uf1000::on_action_DecodeSetup_triggered()
{
    this->show();
    Uf1000_Setup *setup = new Uf1000_Setup(this);
    setup->exec();
}
