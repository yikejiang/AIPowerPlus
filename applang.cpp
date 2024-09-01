#include "applang.h"

AppLang::AppLang() {
    appVersion = "1.12";

    listInterfaceLanguage = {"English", "polski", "汉语"};

    listTranslationLanguage = {"English", "polski", "汉语"};

    listAIRole = {"translator", "writing_helper", "writer", "teacher", "programmer", "custom_role", "speaker"};

    listTTSAudioFileSuffix = {".mp3", ".wav"};

    mapTTSVoice = {{"alloy", "Alloy"}, {"echo", "Echo"}, {"fable", "Fable"}, {"onyx", "Onyx"}, {"nova", "Nova"}, {"shimmer", "Shimmer"}};

    listAPIKeyName = {"openai_api_key", "claude_ai_api_key", "gemini_api_key"};

    mapLangEntry = {
        {"app_name", QVariantMap{{"en", "AI Power Plus"}, {"pl", "AI Power Plus"}, {"zh", "AI Power Plus"}}},
        {"ai_role", QVariantMap{{"en", "AI role"}, {"pl", "Rola AI"}, {"zh", "AI 角色"}}},
        {"translator", QVariantMap{{"en", "Translator"}, {"pl", "Tłumacz"}, {"zh", "翻译"}}},
        {"writing_helper", QVariantMap{{"en", "Writing helper"}, {"pl", "Pomocnik pisania"}, {"zh", "写作助手"}}},
        {"writer", QVariantMap{{"en", "Writer"}, {"pl", "Pisarz"}, {"zh", "作家"}}},
        {"teacher", QVariantMap{{"en", "Teacher"}, {"pl", "Nauczyciel"}, {"zh", "教师"}}},
        {"programmer", QVariantMap{{"en", "Programmer"}, {"pl", "Programista"}, {"zh", "程序员"}}},
        {"custom_role", QVariantMap{{"en", "Custom role"}, {"pl", "Rola niestandardowa"}, {"zh", "自定义"}}},
        {"speaker", QVariantMap{{"en", "Speaker"}, {"pl", "Mówca"}, {"zh", "朗读者"}}},
        {"interface_language", QVariantMap{{"en", "Interface language"}, {"pl", "Język interfejsu"}, {"zh", "界面语言"}}},
        {"ai_model", QVariantMap{{"en", "AI model"}, {"pl", "Model AI"}, {"zh", "AI 模型"}}},
        {"user_text", QVariantMap{{"en", "User text"}, {"pl", "Tekst użytkownika"}, {"zh", "用户文本"}}},
        {"translation_language", QVariantMap{{"en", "Translate into"}, {"pl", "Przetłumacz na"}, {"zh", "翻译为"}}},
        {"tts_voice", QVariantMap{{"en", "TTS voice"}, {"pl", "Głos TTS"}, {"zh", "TTS语音"}}},
        {"process", QVariantMap{{"en", "Process"}, {"pl", "Przetwarzaj"}, {"zh", "处理"}}},
        {"play_audio", QVariantMap{{"en", "Read"}, {"pl", "Czytaj"}, {"zh", "朗读"}}},
        {"play_again", QVariantMap{{"en", "Read again"}, {"pl", "Czytaj ponownie"}, {"zh", "再次朗读"}}},
        {"blackboard", QVariantMap{{"en", "Blackboard"}, {"pl", "Tablica"}, {"zh", "黑板"}}},
        {"ai_text", QVariantMap{{"en", "AI text"}, {"pl", "Tekst AI"}, {"zh", "AI 文本"}}},
        {"user_message", QVariantMap{{"en", "Do you have any idea?"}, {"pl", "Masz jakiś pomysł?"}, {"zh", "你有什么想法？"}}},
        {"chat_context", QVariantMap{{"en", "Enable context"}, {"pl", "Włącz kontekst"}, {"zh", "开启上下文"}}},
        {"submit", QVariantMap{{"en", "Submit"}, {"pl", "Prześlij"}, {"zh", "提交"}}},
        {"explanation", QVariantMap{{"en", "Explanation"}, {"pl", "Wyjaśnienie"}, {"zh", "解释"}}},
        {"chat_history", QVariantMap{{"en", "Realtime conversation"}, {"pl", "Rozmowa w czasie rzeczywistym"}, {"zh", "实时对话"}}},
        {"show_explanation", QVariantMap{{"en", "Show explanation"}, {"pl", "Pokaż wyjaśnienie"}, {"zh", "显示解释"}}},
        {"show_chat_history", QVariantMap{{"en", "Show chat history"}, {"pl", "Pokaż historię czatu"}, {"zh", "显示对话历史"}}},
        {"clear", QVariantMap{{"en", "Clear"}, {"pl", "Wyczyść"}, {"zh", "清空"}}},
        {"settings", QVariantMap{{"en", "Settings"}, {"pl", "Ustawienia"}, {"zh", "设置"}}},
        {"ai_model_configuration", QVariantMap{{"en", "Configure AI model"}, {"pl", "Skonfiguruj model AI"}, {"zh", "调整AI模型"}}},
        {"tts_audio_file_name", QVariantMap{{"en", "TTS audio file name"}, {"pl", "Nazwa pliku audio TTS"}, {"zh", "TTS语音文件名称"}}},
        {"folder_to_save_file", QVariantMap{{"en", "Folder to save the file"}, {"pl", "Folder do zapisywania pliku"}, {"zh", "保存文件的目录"}}},
        {"set", QVariantMap{{"en", "Set"}, {"pl", "Ustaw"}, {"zh", "设置"}}},
        {"set_folder", QVariantMap{{"en", "Set a folder"}, {"pl", "Ustaw folder"}, {"zh", "设置目录"}}},
        {"ai_model_temperature", QVariantMap{{"en", "Temperature"}, {"pl", "Temperatura"}, {"zh", "温度"}}},
        {"ai_role_description", QVariantMap{{"en", "Role description"}, {"pl", "Rola systemu"}, {"zh", "系统角色"}}},
        {"ai_requirements", QVariantMap{{"en", "Requirements"}, {"pl", "Rola użytkownika"}, {"zh", "用户角色"}}},
        {"ai_models", QVariantMap{{"en", "AI models"}, {"pl", "Modele AI"}, {"zh", "AI 模型"}}},
        {"ai_model_custom_name", QVariantMap{{"en", "Model custom name"}, {"pl", "Nazwa niestandardowa modelu"}, {"zh", "模型自定义名称"}}},
        {"ai_model_name", QVariantMap{{"en", "Model name"}, {"pl", "Nazwa modelu"}, {"zh", "模型名称"}}},
        {"name_exists", QVariantMap{{"en", "The name exists."}, {"pl", "Nazwa istnieje."}, {"zh", "名称已存在。"}}},
        {"modify", QVariantMap{{"en", "Modify"}, {"pl", "Modyfikuj"}, {"zh", "修改"}}},
        {"remove", QVariantMap{{"en", "Remove"}, {"pl", "Usuń"}, {"zh", "删除"}}},
        {"add", QVariantMap{{"en", "Add"}, {"pl", "Dodaj"}, {"zh", "添加"}}},
        {"save", QVariantMap{{"en", "Save"}, {"pl", "Zapisz"}, {"zh", "保存"}}},
        {"cancel", QVariantMap{{"en", "Cancel"}, {"pl", "Anuluj"}, {"zh", "取消"}}},
        {"api_keys", QVariantMap{{"en", "API keys"}, {"pl", "Klucze API"}, {"zh", "API 密钥"}}},
        {"openai_api_key", QVariantMap{{"en", "OpenAI API key"}, {"pl", "Klucz API OpenAI"}, {"zh", "OpenAI API 密钥"}}},
        {"claude_ai_api_key", QVariantMap{{"en", "Claude AI API key"}, {"pl", "Klucz API Claude AI"}, {"zh", "Claude AI API 密钥"}}},
        {"gemini_api_key", QVariantMap{{"en", "Gemini API key"}, {"pl", "Klucz API Gemini"}, {"zh", "Gemini API 密钥"}}},
        {"openai_api_key_is_not_found",
         QVariantMap{{"en", "The app cannot find your OpenAI API key. \nPlease input your OpenAI API key here."},
                     {"pl", "Ponieważ aplikacja nie może znaleźć Twojego klucza API OpenAI, \nproszę wprowadź tutaj swój klucz API OpenAI."},
                     {"zh", "OpenAI API 密钥未找到，请在此输入。"}}
        },
        {"openai_api_key_is_saved",
         QVariantMap{{"en", "Your OpenAI API key has been saved."},
                     {"pl", "Twój klucz API OpenAI został zapisany."},
                     {"zh", "OpenAI API 密钥已保存。"}}
        },
        {"input_new_openai_api_key",
         QVariantMap{{"en", "You may input a new OpenAI API key."},
                     {"pl", "Możesz wprowadzić nowy klucz API OpenAI."},
                     {"zh", "现在可以输入新的 OpenAI API 密钥。"}}
        },
        {"claudeai_api_key_is_not_found",
         QVariantMap{{"en", "The app cannot find your Claude AI API key. \nPlease input your Claude AI API key here."},
                     {"pl", "Ponieważ aplikacja nie może znaleźć Twojego klucza API Claude AI, \nproszę wprowadź tutaj swój klucz API Claude AI."},
                     {"zh", "Claude AI API 密钥未找到，请在此输入。"}}
        },
        {"claudeai_api_key_is_saved",
         QVariantMap{{"en", "Your Claude AI API key has been saved."},
                     {"pl", "Twój klucz API Claude AI został zapisany."},
                     {"zh", "Claude AI API 密钥已保存。"}}
        },
        {"input_new_claudeai_api_key",
         QVariantMap{{"en", "You may input a new Claude AI API key."},
                     {"pl", "Możesz wprowadzić nowy klucz API Claude AI."},
                     {"zh", "现在可以输入新的 Claude AI API 密钥。"}}
        },
        {"gemini_api_key_is_not_found",
         QVariantMap{{"en", "The app cannot find your Gemini API key. \nPlease input your Gemini API key here."},
                     {"pl", "Ponieważ aplikacja nie może znaleźć Twojego klucza API Gemini, \nproszę wprowadź tutaj swój klucz API Gemini."},
                     {"zh", "Gemini API 密钥未找到，请在此输入。"}}
        },
        {"gemini_api_key_is_saved",
         QVariantMap{{"en", "Your Gemini API key has been saved."},
                     {"pl", "Twój klucz API Gemini został zapisany."},
                     {"zh", "Gemini API 密钥已保存。"}}
        },
        {"input_new_gemini_api_key",
         QVariantMap{{"en", "You may input a new Gemini API key."},
                     {"pl", "Możesz wprowadzić nowy klucz API Gemini."},
                     {"zh", "现在可以输入新的 Gemini API 密钥。"}}
        },
        {"here_is_my", QVariantMap{{"en", "Here is my "}, {"pl", "To jest "}, {"zh", "这是我"}}},
        {"translation", QVariantMap{{"en", "translation"}, {"pl", "tłumaczenie"}, {"zh", "译好的文本"}}},
        {"modified_text", QVariantMap{{"en", "modified text"}, {"pl", "zmodyfikowany tekst"}, {"zh", ""}}},
        {"written_text", QVariantMap{{"en", "written text"}, {"pl", "napisany tekst"}, {"zh", ""}}},
        {"watch_blackboard", QVariantMap{{"en", "Please watch the blackboard"}, {"pl", "Proszę patrzeć na tablicę"}, {"zh", "请看黑板"}}},
        {"here_is_my_explanation", QVariantMap{{"en", "Here is my explanation"}, {"pl", "To jest moje wyjaśnienie"}, {"zh", "这是我的解释"}}},
        {"software_note",
         QVariantMap{{"en", "AI Translator Plus is released as free software "
                            "under GNU General Public License version 3.\n\n"
                            "AI Translator Plus uses Qt libraries dynamically "
                            "under GNU Lesser General Public License version 3. \n\n"
                            "There is no modification in Qt source code.\n\n"
                            "For more information, please visit https://www.aipowerplus.com ."},
                     {"pl", "AI Translator Plus jest wydany jako wolne oprogramowanie "
                            "na podstawie Powszechnej Licencji Publicznej GNU w wersji 3.\n\n"
                            "AI Translator Plus korzysta dynamicznie z bibliotek Qt "
                            "na podstawie Mniejszej Powszechnej Licencji Publicznej GNU w wersji 3.\n\n"
                            "Kod źródłowy Qt nie został w żaden sposób zmodyfikowany.\n\n"
                            "Aby uzyskać więcej informacji, odwiedź stronę https://www.aipowerplus.com ."},
                     {"zh", "AI Translator Plus 基于 GNU 通用公共许可证第3版作为自由软件发布。\n\n"
                            "AI Translator Plus 根据 GNU 宽通用公共许可证第3版动态使用Qt库。\n\n"
                            "没有对 Qt 源代码作任何修改。\n\n"
                            "欲了解更多信息，请访问 https://www.aipowerplus.com 。"}}}
    };
}

QString AppLang::readLangEntry(const int &indexInterfaceLanguage, const QString &nameLangEntry) {
    QString valueLangEntry;

    if (indexInterfaceLanguage == 1) {
        valueLangEntry = mapLangEntry[nameLangEntry].toMap()["pl"].toString();
    } else if (indexInterfaceLanguage == 2) {
        valueLangEntry = mapLangEntry[nameLangEntry].toMap()["zh"].toString();
    } else {
        valueLangEntry = mapLangEntry[nameLangEntry].toMap()["en"].toString();
    }

    return valueLangEntry;
}

QString AppLang::readInterfaceLanguage(const int &indexInterfaceLanguage) {
    QString interfaceLanguage = listInterfaceLanguage.at(indexInterfaceLanguage);
    return interfaceLanguage;
}

QString AppLang::readTranslationLanguage(const int &indexTranslationLanguage) {
    QString translationLanguage = listTranslationLanguage.at(indexTranslationLanguage);
    return translationLanguage;
}

QList<QString> AppLang::readComboboxItemsAIRole(const int &indexInterfaceLanguage) {
    QList<QString> listComboboxItemsAIRole;
    for (const QString &item : listAIRole) {
        QString langItem = readLangEntry(indexInterfaceLanguage, item);
        listComboboxItemsAIRole.append(langItem);
    }

    return listComboboxItemsAIRole;
}

QString AppLang::readAIRole(const int &indexAIRole) {
    QString aiRole = listAIRole.at(indexAIRole);
    return aiRole;
}

QList<QString> AppLang::readComboboxItemsTTSVoice() {
    QList<QString> listItemsTTSVoice = mapTTSVoice.values();
    return listItemsTTSVoice;
}

QString AppLang::readTTSVoice(const int &indexTTSVoice) {
    QList<QString> listTTSVoice = mapTTSVoice.keys();
    QString ttsVoice = listTTSVoice.at(indexTTSVoice);
    return ttsVoice;
}

QList<QString> AppLang::readComboboxItemsAPIKeyName(const int &indexInterfaceLanguage) {
    QList<QString> listComboboxItemsAPIKeyName;
    for (const QString &item : listAPIKeyName)
    {
        QString langItem = readLangEntry(indexInterfaceLanguage, item);
        listComboboxItemsAPIKeyName.append(langItem);
    }

    return listComboboxItemsAPIKeyName;
}

QString AppLang::readAPIKeyName(const int& indexAPIKeyName) {
    QString apiKeyName = listAPIKeyName.at(indexAPIKeyName);
    return apiKeyName;
}
