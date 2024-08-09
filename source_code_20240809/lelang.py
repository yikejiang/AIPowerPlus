class LELang:
    def __init__(self):
        super(LELang, self).__init__()

        self.expert_mode = ['translator_mode',
                            'writing_helper_mode',
                            'writer_mode',
                            'teacher_mode',
                            'programmer_mode',
                            'free_mode',
                            'speaker_mode']

        self.interface_language = ['English',
                                   'polski',
                                   '汉语']

        self.translation_language = ['English',
                                     'polski',
                                     '汉语']

        self.tts_voice_list = ['alloy', 'echo', 'fable', 'onyx', 'nova', 'shimmer']
        self.tts_voice_name = ['Alloy', 'Echo', 'Fable', 'Onyx', 'Nova', 'Shimmer']

        self.entry_list = ['app_name',
                           'expert_mode',
                           'translator_mode',
                           'writing_helper_mode',
                           'writer_mode',
                           'teacher_mode',
                           'programmer_mode',
                           'free_mode',
                           'speaker_mode',
                           'interface_language',
                           'ai_model',
                           'user_text',
                           'process',
                           'translation_language',
                           'tts_voice',
                           'play_audio',
                           'play_again',
                           'ai_text_label',
                           'blackboard',
                           'explanation',
                           'user_message_label',
                           'chat_context_option',
                           'submit_button',
                           'chat_history',
                           'show_ai_comments',
                           'show_chat_history',
                           'clear',
                           'settings',
                           'settings_expert_mode',
                           'temperature',
                           'settings_expert_mode_system_role_label',
                           'settings_expert_mode_user_role_label',
                           'ai_models',
                           'ai_model_custom_name',
                           'ai_model_name',
                           'modify',
                           'remove',
                           'add',
                           'cancel',
                           'setting_api_keys',
                           'openai_api_key_not_found',
                           'openai_api_key_saved',
                           'input_new_openai_api_key',
                           'claudeai_api_key_not_found',
                           'claudeai_api_key_saved',
                           'input_new_claudeai_api_key',
                           'gemini_api_key_not_found',
                           'gemini_api_key_saved',
                           'input_new_gemini_api_key',
                           'save',
                           'change',
                           'here_is_my',
                           'here_is_my_explanation',
                           'translation',
                           'modified text',
                           'written text',
                           'watch_blackboard',
                           'software_note']

        self. entry_translations_list_en = ['AI Power Plus',
                                            'Expert Mode',
                                            'Translator',
                                            'Writing Helper',
                                            'Writer',
                                            'Teacher',
                                            'Programmer',
                                            'Free Mode',
                                            'Speaker',
                                            'Interface Language',
                                            'AI Model',
                                            'User text',
                                            'Process',
                                            'Translate into',
                                            'TTS voice',
                                            'Read',
                                            'Read again',
                                            'AI text',
                                            'Blackboard',
                                            'Explanation',
                                            'Do you have any idea',
                                            'Enable context',
                                            'Submit',
                                            'Realtime Conversation',
                                            'Show explanation',
                                            'Show chat history',
                                            'Clear',
                                            'Settings',
                                            'Edit Expert Mode Guideline',
                                            'Temperature',
                                            'System Role',
                                            'User Role',
                                            'AI models',
                                            'Model custom name',
                                            'Model name',
                                            'Modify',
                                            'Remove',
                                            'Add',
                                            'Cancel',
                                            'Set API keys',
                                            'Because the app cannot find your OpenAI API key, \nplease input your OpenAI API key here.',
                                            'Your OpenAI API key has been saved.',
                                            'You may input a new OpenAI API key.',
                                            'Because the app cannot find your Claude AI API key, \nplease input your Claude AI API key here.',
                                            'Your Claude AI API key has been saved.',
                                            'You may input a new Claude AI API key.',
                                            'Because the app cannot find your Gemini API key, \nplease input your Gemini API key here.',
                                            'Your Gemini API key has been saved.',
                                            'You may input a new Gemini API key.',
                                            'Save',
                                            'Change',
                                            'Here is my ',
                                            'Here is my explanation',
                                            'translation',
                                            'modified text',
                                            'written text',
                                            'Please watch the blackboard',
                                            'AI Power Plus is released as free software\n\n'
                                            'under GNU General Public License version 3.\n\n'
                                            'AI Power Plus uses Qt libraries dynamically \n\n'
                                            'under GNU Lesser General Public License version 3. \n\n'
                                            'There is no modification in Qt source code.\n\n'
                                            'For more information, please visit:']

        self.entry_translations_list_pl = ['AI Power Plus',
                                           'Tryb eksperta',
                                           'Tłumacz',
                                           'Pomocnik pisania',
                                           'Pisarz',
                                           'Nauczyciel',
                                           'Programista',
                                           'Tryb wolny',
                                           'Mówca',
                                           'Język interfejsu',
                                           'Model AI',
                                           'Tekst użytkownika',
                                           'Przetwarzaj',
                                           'Przetłumacz na',
                                           'Głos TTS',
                                           'Czytaj',
                                           'Czytaj ponownie',
                                           'Tekst AI',
                                           'Tablica',
                                           'Wyjaśnienie',
                                           'Masz jakiś pomysł',
                                           'Włącz kontekst',
                                           'Prześlij',
                                           'Rozmowa w czasie rzeczywistym',
                                           'Pokaż wyjaśnienie',
                                           'Pokaż historię czatu',
                                           'Wyczyść',
                                           'Ustawienia',
                                           'Edytuj wytyczne trybu eksperta',
                                           'Temperatura',
                                           'Rola systemu',
                                           'Rola użytkownika',
                                           'Modele AI',
                                           'Nazwa niestandardowa modelu',
                                           'Nazwa modelu',
                                           'Modyfikuj',
                                           'Usuń',
                                           'Dodaj',
                                           'Anuluj',
                                           'Ustaw klucze API',
                                           'Ponieważ aplikacja nie może znaleźć Twojego klucza API OpenAI, \nproszę wprowadź tutaj swój klucz API OpenAI.',
                                           'Twój klucz API OpenAI został zapisany.',
                                           'Możesz wprowadzić nowy klucz API OpenAI.',
                                           'Ponieważ aplikacja nie może znaleźć Twojego klucza API Claude AI, \nproszę wprowadź tutaj swój klucz API Claude AI.',
                                           'Twój klucz API Claude AI został zapisany.',
                                           'Możesz wprowadzić nowy klucz API Claude AI.',
                                           'Ponieważ aplikacja nie może znaleźć Twojego klucza API Gemini, \nproszę wprowadź tutaj swój klucz API Gemini.',
                                           'Twój klucz API Gemini został zapisany.',
                                           'Możesz wprowadzić nowy klucz API Gemini.',
                                           'Zapisz',
                                           'Zmień',
                                           'Oto jest ',
                                           'oto jest moje wyjaśnienie',
                                           'tłumaczenie',
                                           'zmodyfikowany tekst',
                                           'napisany tekst',
                                           'Proszę patrzeć na tablicę',
                                           'AI Power Plus jest wydany jako wolne oprogramowanie\n\n'
                                           'na podstawie Powszechnej Licencji Publicznej GNU w wersji 3.\n\n'
                                           'AI Power Plus korzysta dynamicznie z bibliotek Qt\n\n'
                                           'na podstawie Mniejszej Powszechnej Licencji Publicznej GNU w wersji 3.\n\n'
                                           'Kod źródłowy Qt nie został w żaden sposób zmodyfikowany.\n\n'
                                           'Aby uzyskać więcej informacji, odwiedź stronę:']

        self.entry_translations_list_zh = ['AI Power Plus',
                                           '专家模式',
                                           '翻译家',
                                           '写作助手',
                                           '作家',
                                           '教师',
                                           '程序员',
                                           '自由模式',
                                           '语音模式',
                                           '界面语言',
                                           'AI 模型',
                                           '用户文本',
                                           '处理',
                                           '翻译为',
                                           '语音风格',
                                           '朗读',
                                           '再次朗读',
                                           'AI 文本',
                                           '黑板',
                                           '解释',
                                           '你有什么想法',
                                           '开启上下文',
                                           '提交',
                                           '实时对话',
                                           '显示解释',
                                           '显示对话历史',
                                           '清空',
                                           '设置',
                                           '修改专家模式规则',
                                           '温度',
                                           '系统角色',
                                           '用户角色',
                                           'AI 模型',
                                           '模型自定义名称',
                                           '模型名称',
                                           '修改',
                                           '删除',
                                           '添加',
                                           '取消',
                                           '设置 API key',
                                           '未找到 OpenAI API key，请在此输入。',
                                           'OpenAI API key 已保存。',
                                           '现在可以输入新的 OpenAI API key。',
                                           '未找到 Claude AI API key，请在此输入。',
                                           'Claude AI API key 已保存。',
                                           '现在可以输入新的 Claude AI API key。',
                                           '未找到 Gemini API key，请在此输入。',
                                           'Gemini API key 已保存。',
                                           '现在可以输入新的 Gemini API key。',
                                           '保存',
                                           '更改',
                                           '这是我',
                                           '这是我的解释',
                                           '译好的文本',
                                           '修改好的文本',
                                           '写好的文本',
                                           '请看黑板',
                                           'AI Power Plus基于GNU通用公共许可证第3版作为自由软件发布。\n\n'
                                           'AI Power Plus根据GNU宽通用公共许可证第3版动态使用Qt库。\n\n'
                                           '没有对Qt源代码作任何修改。\n\n'
                                           '欲了解更多信息，请访问：']

    def get_lang(self, interface_language_index, entry):
        entry_index = self.entry_list.index(entry)

        if interface_language_index == 1:
            lang_translation = self.entry_translations_list_pl[entry_index]
        elif interface_language_index == 2:
            lang_translation = self.entry_translations_list_zh[entry_index]
        else:
            lang_translation = self.entry_translations_list_en[entry_index]

        return lang_translation

    def get_expert_mode(self, index):
        expert_mode = self.expert_mode[index]

        return expert_mode

    def get_interface_language(self, index):
        interface_language = self.interface_language[index]
        return interface_language

    def get_translation_language(self, index):
        translation_language = self.translation_language[index]
        return translation_language

    def get_tts_voice(self, index):
        tts_voice = self.tts_voice_list[index]
        return tts_voice
