import os
import webbrowser

from PySide6.QtCore import Qt, Slot, Signal
from PySide6.QtGui import QFont, QIcon
from PySide6.QtWidgets import (QTextEdit, QLabel, QPushButton, QVBoxLayout, QHBoxLayout, QDialog,
                               QComboBox, QLineEdit)

from lelang import LELang
from leconfig import Config


class LESettings(QDialog):
    refresh_ai_model_signal = Signal(bool)

    def __init__(self, interface_language_index, expert_mode_index):
        super().__init__()

        # 加载模块
        self.config = Config()
        self.lang = LELang()

        # Logo
        if os.name == 'nt':
            logo_path = self.config.get_logo_path()
            if os.path.exists(logo_path):
                self.setWindowIcon(QIcon(logo_path))

        self.setGeometry(0, 0, 800, 600)

        self.modify_ai_model_index = -1

        self.openai_api_key_status = False
        self.openai_api_key_change_status = False
        self.claudeai_api_key_status = False
        self.claudeai_api_key_change_status = False
        self.gemini_api_key_status = False
        self.gemini_api_key_change_status = False

        self.interface_language_index = interface_language_index
        self.expert_mode_index = expert_mode_index

        self.expert_mode = self.lang.get_expert_mode(self.expert_mode_index)
        self.settings_expert_mode_entry = self.expert_mode

        font = QFont()
        font.setPointSize(12)

        # 总体布局
        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        # 顶部布局
        self.layout_top = QHBoxLayout()
        self.layout_top.setAlignment(Qt.AlignmentFlag.AlignTop)
        self.layout.addLayout(self.layout_top)

        self.layout_top_right = QHBoxLayout()
        self.layout_top_right.setAlignment(Qt.AlignmentFlag.AlignRight)
        self.layout_top.addLayout(self.layout_top_right)

        # 主要部件的布局
        self.layout_main = QHBoxLayout()
        self.layout.addLayout(self.layout_main)

        # 左侧主要部件布局
        self.layout_main_left = QVBoxLayout()
        self.layout_main_left.setAlignment(Qt.AlignmentFlag.AlignTop)
        self.layout_main.addLayout(self.layout_main_left)

        # 左侧主要部件顶部布局
        self.layout_main_left_top = QHBoxLayout()
        self.layout_main_left.addLayout(self.layout_main_left_top)

        # 左侧顶部靠左部件布局
        self.layout_main_left_top_left = QHBoxLayout()
        self.layout_main_left_top_left.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_left_top.addLayout(self.layout_main_left_top_left)

        # 左侧中部布局
        self.layout_main_left_center = QVBoxLayout()
        self.layout_main_left.addLayout(self.layout_main_left_center)

        # 左侧下部布局
        self.layout_main_left_bottom = QVBoxLayout()
        self.layout_main_left.addLayout(self.layout_main_left_bottom)

        # 右侧主要部件布局
        self.layout_main_right = QVBoxLayout()
        self.layout_main_right.setAlignment(Qt.AlignmentFlag.AlignTop)
        self.layout_main.addLayout(self.layout_main_right)

        # 右侧顶部布局
        self.layout_main_right_top = QVBoxLayout()
        self.layout_main_right.addLayout(self.layout_main_right_top)

        self.layout_main_right_top_first = QHBoxLayout()
        self.layout_main_right_top_first.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_right_top.addLayout(self.layout_main_right_top_first)

        self.layout_main_right_top_second = QHBoxLayout()
        self.layout_main_right_top_second.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_right_top.addLayout(self.layout_main_right_top_second)

        self.layout_main_right_top_third = QHBoxLayout()
        self.layout_main_right_top_third.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_right_top.addLayout(self.layout_main_right_top_third)

        self.layout_main_right_top_fourth = QHBoxLayout()
        self.layout_main_right_top_fourth.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_right_top.addLayout(self.layout_main_right_top_fourth)

        # 右侧中部布局
        self.layout_main_right_center = QVBoxLayout()
        self.layout_main_right_center.setContentsMargins(0, 20, 0, 0)
        self.layout_main_right.addLayout(self.layout_main_right_center)

        self.layout_main_right_center_left = QHBoxLayout()
        self.layout_main_right_center.addLayout(self.layout_main_right_center_left)

        # 右侧底部布局
        self.layout_main_right_bottom = QVBoxLayout()
        self.layout_main_right_bottom.setContentsMargins(0, 20, 0, 0)
        self.layout_main_right.addLayout(self.layout_main_right_bottom)

        # 设置界面
        # 设置模式规则
        self.settings_expert_mode_label = QLabel()
        self.layout_main_left_top_left.addWidget(self.settings_expert_mode_label)

        self.settings_expert_mode_chooser = QComboBox()
        self.settings_expert_mode_chooser.setFixedWidth(150)
        self.settings_expert_mode_chooser.addItems(self.lang.expert_mode)
        self.settings_expert_mode_chooser.setCurrentIndex(self.expert_mode_index)
        self.layout_main_left_top_left.addWidget(self.settings_expert_mode_chooser)

        self.settings_expert_mode_temperature_label = QLabel()
        self.layout_main_left_center.addWidget(self.settings_expert_mode_temperature_label)

        self.settings_expert_mode_temperature_input = QLineEdit()
        self.settings_expert_mode_temperature_input.setFixedWidth(40)
        self.layout_main_left_center.addWidget(self.settings_expert_mode_temperature_input)

        self.settings_expert_mode_system_role_label = QLabel()
        self.layout_main_left_center.addWidget(self.settings_expert_mode_system_role_label)

        self.settings_expert_mode_system_role_text = QTextEdit()
        self.settings_expert_mode_system_role_text.setFont(font)
        self.settings_expert_mode_system_role_text.setFixedWidth(450)
        self.settings_expert_mode_system_role_text.setFixedHeight(150)
        self.settings_expert_mode_system_role_text.setAcceptRichText(False)
        self.layout_main_left_center.addWidget(self.settings_expert_mode_system_role_text)

        self.settings_expert_mode_user_role_label = QLabel()
        self.layout_main_left_center.addWidget(self.settings_expert_mode_user_role_label)

        self.settings_expert_mode_user_role_text = QTextEdit()
        self.settings_expert_mode_user_role_text.setFont(font)
        self.settings_expert_mode_user_role_text.setFixedWidth(450)
        self.settings_expert_mode_user_role_text.setAcceptRichText(False)
        self.layout_main_left_center.addWidget(self.settings_expert_mode_user_role_text)

        self.read_expert_mode_guidelines(self.settings_expert_mode_entry)

        # AI 模型
        self.ai_models_label = QLabel()
        self.layout_main_right_top_first.addWidget(self.ai_models_label)

        self.ai_model_custom_name_label = QLabel()
        self.layout_main_right_top_second.addWidget(self.ai_model_custom_name_label)

        self.ai_models_combobox = QComboBox()
        self.ai_models_combobox.setFixedWidth(180)
        self.layout_main_right_top_second.addWidget(self.ai_models_combobox)

        self.ai_model_custom_name_input = QLineEdit()
        self.ai_model_custom_name_input.setFixedWidth(180)
        self.layout_main_right_top_second.addWidget(self.ai_model_custom_name_input)

        self.ai_model_modify_button = QPushButton()
        self.ai_model_remove_button = QPushButton()
        self.ai_model_add_button = QPushButton()

        self.ai_model_save_button = QPushButton()
        self.ai_model_cancel_button = QPushButton()

        self.layout_main_right_top_third.addWidget(self.ai_model_modify_button)
        self.layout_main_right_top_third.addWidget(self.ai_model_remove_button)
        self.layout_main_right_top_third.addWidget(self.ai_model_add_button)
        self.layout_main_right_top_third.addWidget(self.ai_model_save_button)
        self.layout_main_right_top_third.addWidget(self.ai_model_cancel_button)

        self.ai_model_name_label = QLabel()
        self.layout_main_right_top_fourth.addWidget(self.ai_model_name_label)

        self.ai_model_name_input = QLineEdit()
        self.ai_model_name_input.setFixedWidth(180)
        self.layout_main_right_top_fourth.addWidget(self.ai_model_name_input)

        # 设置API
        self.api_keys_label = QLabel()
        self.layout_main_right_center_left.addWidget(self.api_keys_label)

        # 设置OpenAI API
        self.openai_api_key_label = QLabel()
        self.layout_main_right_center.addWidget(self.openai_api_key_label)

        self.openai_api_key_input = QLineEdit()
        self.openai_api_key_input.setFixedWidth(200)
        self.layout_main_right_center.addWidget(self.openai_api_key_input)

        self.openai_api_key_save_button = QPushButton()
        self.openai_api_key_save_button.setEnabled(False)
        self.openai_api_key_save_button.setFixedSize(80, 25)
        self.layout_main_right_center.addWidget(self.openai_api_key_save_button)
        self.openai_api_key_save_button.clicked.connect(self.save_openai_api_key)

        self.openai_api_key_change_button = QPushButton()
        self.openai_api_key_change_button.setVisible(False)
        self.openai_api_key_change_button.setFixedSize(80, 25)
        self.layout_main_right_center.addWidget(self.openai_api_key_change_button)
        self.openai_api_key_change_button.clicked.connect(self.change_openai_api_key)

        # 设置Claude AI API
        self.claudeai_api_key_label = QLabel()
        self.layout_main_right_center.addWidget(self.claudeai_api_key_label)

        self.claudeai_api_key_input = QLineEdit()
        self.claudeai_api_key_input.setFixedWidth(200)
        self.layout_main_right_center.addWidget(self.claudeai_api_key_input)

        self.claudeai_api_key_save_button = QPushButton()
        self.claudeai_api_key_save_button.setEnabled(False)
        self.claudeai_api_key_save_button.setFixedSize(80, 25)
        self.layout_main_right_center.addWidget(self.claudeai_api_key_save_button)
        self.claudeai_api_key_save_button.clicked.connect(self.save_claudeai_api_key)

        self.claudeai_api_key_change_button = QPushButton()
        self.claudeai_api_key_change_button.setVisible(False)
        self.claudeai_api_key_change_button.setFixedSize(80, 25)
        self.layout_main_right_center.addWidget(self.claudeai_api_key_change_button)
        self.claudeai_api_key_change_button.clicked.connect(self.change_claudeai_api_key)

        # 设置Gemini API
        # 设置Claude AI API
        self.gemini_api_key_label = QLabel()
        self.layout_main_right_center.addWidget(self.gemini_api_key_label)

        self.gemini_api_key_input = QLineEdit()
        self.gemini_api_key_input.setFixedWidth(200)
        self.layout_main_right_center.addWidget(self.gemini_api_key_input)

        self.gemini_api_key_save_button = QPushButton()
        self.gemini_api_key_save_button.setEnabled(False)
        self.gemini_api_key_save_button.setFixedSize(80, 25)
        self.layout_main_right_center.addWidget(self.gemini_api_key_save_button)
        self.gemini_api_key_save_button.clicked.connect(self.save_gemini_api_key)

        self.gemini_api_key_change_button = QPushButton()
        self.gemini_api_key_change_button.setVisible(False)
        self.gemini_api_key_change_button.setFixedSize(80, 25)
        self.layout_main_right_center.addWidget(self.gemini_api_key_change_button)
        self.gemini_api_key_change_button.clicked.connect(self.change_gemini_api_key)

        # 软件信息
        self.software_version_label = QLabel()
        self.layout_main_right_bottom.addWidget(self.software_version_label)

        self.software_note_label = QLabel()
        self.layout_main_right_bottom.addWidget(self.software_note_label)

        self.software_website_label = QLabel()
        self.software_website_label.setText('<a href="https://www.aipowerplus.com">https://www.aipowerplus.com</a>')
        self.layout_main_right_bottom.addWidget(self.software_website_label)

        # 启动时执行
        self.check_api_keys()
        self.reload_ai_models()
        self.set_lang_text()

        # 设置信号发送
        self.settings_expert_mode_chooser.currentIndexChanged.connect(self.settings_change_expert_mode_entry)
        self.settings_expert_mode_temperature_input.textChanged.connect(self.save_temperature)
        self.settings_expert_mode_system_role_text.textChanged.connect(self.save_expert_mode_system_role)
        self.settings_expert_mode_user_role_text.textChanged.connect(self.save_expert_mode_user_role)

        self.ai_models_combobox.currentIndexChanged.connect(self.settings_ai_model_index_changed)
        self.ai_model_modify_button.clicked.connect(self.modify_ai_model)
        self.ai_model_remove_button.clicked.connect(self.remove_ai_model)
        self.ai_model_add_button.clicked.connect(self.add_ai_model)
        self.ai_model_save_button.clicked.connect(self.save_ai_model)
        self.ai_model_cancel_button.clicked.connect(self.cancel_modify_or_add_ai_model)

        self.openai_api_key_input.textChanged.connect(self.input_openai_api_key)
        self.claudeai_api_key_input.textChanged.connect(self.input_claudeai_api_key)
        self.gemini_api_key_input.textChanged.connect(self.input_gemini_api_key)
        self.openai_api_key_save_button.clicked.connect(self.save_openai_api_key)
        self.claudeai_api_key_save_button.clicked.connect(self.save_claudeai_api_key)
        self.gemini_api_key_save_button.clicked.connect(self.save_gemini_api_key)

        self.software_website_label.linkActivated.connect(self.open_link)

    @staticmethod
    def open_link():
        webbrowser.open('https://www.aipowerplus.com')

    @Slot()
    def change_interface_language_index(self, index):
        self.interface_language_index = index
        self.set_lang_text()

    @Slot()
    def change_expert_mode_index(self, index):
        self.expert_mode_index = index
        self.settings_expert_mode_chooser.setCurrentIndex(self.expert_mode_index)
        self.settings_change_expert_mode_entry(self.expert_mode_index)

    @Slot()
    def settings_change_expert_mode_entry(self, index):
        self.settings_expert_mode_entry = self.lang.get_expert_mode(index)

        self.read_expert_mode_guidelines(self.settings_expert_mode_entry)

    @Slot()
    def save_temperature(self):
        expert_mode_entry = self.settings_expert_mode_entry
        temperature = self.settings_expert_mode_temperature_input.text()
        self.config.save_expert_mode_config(expert_mode_entry, 'temperature', temperature)

    @Slot()
    def save_expert_mode_system_role(self):
        expert_mode_entry = self.settings_expert_mode_entry
        guidelines_type = 'role'
        guidelines_value = self.settings_expert_mode_system_role_text.toPlainText()
        self.config.save_expert_mode_guidelines(expert_mode_entry, guidelines_type, guidelines_value)

    @Slot()
    def save_expert_mode_user_role(self):
        expert_mode_entry = self.settings_expert_mode_entry
        guidelines_type = 'requirements'
        guidelines_value = self.settings_expert_mode_user_role_text.toPlainText()
        self.config.save_expert_mode_guidelines(expert_mode_entry, guidelines_type, guidelines_value)

    def set_lang_text(self):
        if self.interface_language_index == 0:
            self.ai_model_custom_name_label.setFixedWidth(135)
            self.ai_model_name_label.setFixedWidth(90)
        if self.interface_language_index == 1:
            self.ai_model_custom_name_label.setFixedWidth(195)
            self.ai_model_name_label.setFixedWidth(100)
        if self.interface_language_index == 2:
            self.ai_model_custom_name_label.setFixedWidth(95)
            self.ai_model_name_label.setFixedWidth(60)

        self.setWindowTitle(self.lang.get_lang(self.interface_language_index, 'settings'))

        self.settings_expert_mode_label.setText(
            self.lang.get_lang(self.interface_language_index, 'settings_expert_mode'))

        self.settings_expert_mode_chooser.setItemText(0, self.lang.get_lang(self.interface_language_index,
                                                                            'translator_mode'))
        self.settings_expert_mode_chooser.setItemText(1,
                                                      self.lang.get_lang(self.interface_language_index,
                                                                         'writing_helper_mode'))
        self.settings_expert_mode_chooser.setItemText(2,
                                                      self.lang.get_lang(self.interface_language_index, 'writer_mode'))
        self.settings_expert_mode_chooser.setItemText(3,
                                                      self.lang.get_lang(self.interface_language_index, 'teacher_mode'))
        self.settings_expert_mode_chooser.setItemText(4, self.lang.get_lang(self.interface_language_index, 'programmer_mode'))
        self.settings_expert_mode_chooser.setItemText(5, self.lang.get_lang(self.interface_language_index, 'free_mode'))
        self.settings_expert_mode_chooser.setItemText(6,
                                                      self.lang.get_lang(self.interface_language_index, 'speaker_mode'))

        self.settings_expert_mode_temperature_label.setText(
            self.lang.get_lang(self.interface_language_index, 'temperature'))

        self.settings_expert_mode_system_role_label.setText(
            self.lang.get_lang(self.interface_language_index, 'settings_expert_mode_system_role_label'))
        self.settings_expert_mode_user_role_label.setText(
            self.lang.get_lang(self.interface_language_index, 'settings_expert_mode_user_role_label'))

        self.ai_models_label.setText(self.lang.get_lang(self.interface_language_index, 'ai_models'))

        self.ai_model_custom_name_label.setText(self.lang.get_lang(self.interface_language_index, 'ai_model_custom_name'))
        self.ai_model_name_label.setText(self.lang.get_lang(self.interface_language_index, 'ai_model_name'))

        self.ai_model_modify_button.setText(self.lang.get_lang(self.interface_language_index, 'modify'))
        self.ai_model_remove_button.setText(self.lang.get_lang(self.interface_language_index, 'remove'))
        self.ai_model_add_button.setText(self.lang.get_lang(self.interface_language_index, 'add'))
        self.ai_model_save_button.setText(self.lang.get_lang(self.interface_language_index, 'save'))
        self.ai_model_cancel_button.setText(self.lang.get_lang(self.interface_language_index, 'cancel'))

        self.api_keys_label.setText(self.lang.get_lang(self.interface_language_index, 'setting_api_keys'))

        self.openai_api_key_save_button.setText(self.lang.get_lang(self.interface_language_index, 'save'))
        self.openai_api_key_change_button.setText(self.lang.get_lang(self.interface_language_index, 'change'))

        self.claudeai_api_key_save_button.setText(self.lang.get_lang(self.interface_language_index, 'save'))
        self.claudeai_api_key_change_button.setText(self.lang.get_lang(self.interface_language_index, 'change'))

        self.gemini_api_key_save_button.setText(self.lang.get_lang(self.interface_language_index, 'save'))
        self.gemini_api_key_change_button.setText(self.lang.get_lang(self.interface_language_index, 'change'))

        self.software_version_label.setText('AI Power Plus 1.0\n')
        self.software_note_label.setText(self.lang.get_lang(self.interface_language_index, 'software_note'))

        self.set_lang_text_settings_api_keys()

    def set_lang_text_settings_api_keys(self):
        if self.openai_api_key_status is False:
            self.openai_api_key_label.setText(
                self.lang.get_lang(self.interface_language_index, 'openai_api_key_not_found'))
        else:
            if self.openai_api_key_change_status is False:
                self.openai_api_key_label.setText(self.lang.get_lang(self.interface_language_index, 'openai_api_key_saved'))
            else:
                self.openai_api_key_label.setText(
                    self.lang.get_lang(self.interface_language_index, 'input_new_openai_api_key'))

        if self.claudeai_api_key_status is False:
            self.claudeai_api_key_label.setText(
                self.lang.get_lang(self.interface_language_index, 'claudeai_api_key_not_found'))
        else:
            if self.claudeai_api_key_change_status is False:
                self.claudeai_api_key_label.setText(self.lang.get_lang(self.interface_language_index, 'claudeai_api_key_saved'))
            else:
                self.claudeai_api_key_label.setText(
                    self.lang.get_lang(self.interface_language_index, 'input_new_claudeai_api_key'))

        if self.gemini_api_key_status is False:
            self.gemini_api_key_label.setText(
                self.lang.get_lang(self.interface_language_index, 'gemini_api_key_not_found'))
        else:
            if self.gemini_api_key_change_status is False:
                self.gemini_api_key_label.setText(self.lang.get_lang(self.interface_language_index, 'gemini_api_key_saved'))
            else:
                self.gemini_api_key_label.setText(
                    self.lang.get_lang(self.interface_language_index, 'input_new_gemini_api_key'))

    def read_expert_mode_guidelines(self, expert_mode):
        expert_role, expert_requirements = self.config.read_expert_mode_guidelines(expert_mode)
        expert_temperature = self.config.read_expert_mode_config(expert_mode, 'temperature')

        expert_role = ''.join(expert_role)
        expert_requirements = ''.join(expert_requirements)

        self.settings_expert_mode_temperature_input.setText(expert_temperature)
        self.settings_expert_mode_system_role_text.setText(expert_role)
        self.settings_expert_mode_user_role_text.setText(expert_requirements)

    def reload_ai_models(self):
        ai_model_custom_names, ai_model_names = self.config.read_ai_models()

        self.ai_models_combobox.clear()
        self.ai_models_combobox.addItems(ai_model_custom_names)
        self.ai_models_combobox.setCurrentIndex(0)
        self.ai_models_combobox.setVisible(True)

        self.ai_model_custom_name_label.setVisible(False)
        self.ai_model_custom_name_input.setVisible(False)
        if ai_model_custom_names:
            self.ai_model_custom_name_input.setText(ai_model_custom_names[0])

        if ai_model_names:
            self.ai_model_name_input.setText(ai_model_names[0])

        self.ai_model_name_input.setReadOnly(True)

        self.ai_model_modify_button.setVisible(True)
        self.ai_model_remove_button.setVisible(True)
        self.ai_model_add_button.setVisible(True)
        self.ai_model_save_button.setVisible(False)
        self.ai_model_cancel_button.setVisible(False)

        self.refresh_ai_model_signal.emit(True)

    @Slot()
    def settings_ai_model_index_changed(self, index):
        self.modify_ai_model_index = index

        ai_model_custom_names, ai_model_names = self.config.read_ai_models()

        self.ai_model_custom_name_input.setText(ai_model_custom_names[index])
        self.ai_model_name_input.setText(ai_model_names[index])

    def modify_ai_model(self):
        self.modify_ai_model_index = self.ai_models_combobox.currentIndex()

        self.ai_models_combobox.setVisible(False)

        self.ai_model_custom_name_label.setVisible(True)
        self.ai_model_custom_name_input.setVisible(True)

        self.ai_model_name_input.setReadOnly(False)

        self.ai_model_modify_button.setVisible(False)
        self.ai_model_remove_button.setVisible(False)
        self.ai_model_add_button.setVisible(False)

        self.ai_model_save_button.setVisible(True)
        self.ai_model_cancel_button.setVisible(True)

    def remove_ai_model(self):
        ai_model_index = self.ai_models_combobox.currentIndex()
        self.config.remove_ai_model(ai_model_index)

        self.reload_ai_models()

    def add_ai_model(self):
        self.modify_ai_model_index = -1

        self.ai_model_custom_name_input.clear()
        self.ai_model_name_input.clear()

        self.ai_models_combobox.setVisible(False)
        self.ai_model_custom_name_label.setVisible(True)
        self.ai_model_custom_name_input.setVisible(True)
        self.ai_model_name_input.setReadOnly(False)
        self.ai_model_modify_button.setVisible(False)
        self.ai_model_remove_button.setVisible(False)
        self.ai_model_add_button.setVisible(False)
        self.ai_model_save_button.setVisible(True)
        self.ai_model_cancel_button.setVisible(True)

    def save_ai_model(self):
        if self.modify_ai_model_index == -1:
            ai_model_custom_name = self.ai_model_custom_name_input.text()
            ai_model_name = self.ai_model_name_input.text()
            self.config.add_ai_model(ai_model_custom_name, ai_model_name)
        else:
            ai_model_custom_name = self.ai_model_custom_name_input.text()
            ai_model_name = self.ai_model_name_input.text()
            self.config.modify_ai_model(self.modify_ai_model_index, ai_model_custom_name, ai_model_name)

        self.ai_model_custom_name_input.clear()
        self.ai_model_name_input.clear()

        self.reload_ai_models()

    def cancel_modify_or_add_ai_model(self):
        self.reload_ai_models()

    def check_api_keys(self):
        openai_api_key = self.config.read_configuration('openai_api_key')
        if openai_api_key == '':
            self.openai_api_key_input.setEnabled(True)
            self.openai_api_key_status = False
        else:
            self.openai_api_key_input.setEnabled(False)
            self.openai_api_key_status = True
            self.openai_api_key_change_status = False

        claudeai_api_key = self.config.read_configuration('claudeai_api_key')
        if claudeai_api_key == '':
            self.claudeai_api_key_input.setEnabled(True)
            self.claudeai_api_key_status = False
        else:
            self.claudeai_api_key_input.setEnabled(False)
            self.claudeai_api_key_status = True
            self.claudeai_api_key_change_status = False

        gemini_api_key = self.config.read_configuration('gemini_api_key')
        if gemini_api_key == '':
            self.gemini_api_key_input.setEnabled(True)
            self.gemini_api_key_status = False
        else:
            self.gemini_api_key_input.setEnabled(False)
            self.gemini_api_key_status = True
            self.gemini_api_key_change_status = False

        self.set_lang_text_settings_api_keys()

        if self.openai_api_key_status is False:
            self.openai_api_key_save_button.setVisible(True)
            self.openai_api_key_change_button.setVisible(False)
        else:
            self.openai_api_key_save_button.setVisible(False)
            self.openai_api_key_change_button.setVisible(True)

        if self.claudeai_api_key_status is False:
            self.claudeai_api_key_save_button.setVisible(True)
            self.claudeai_api_key_change_button.setVisible(False)
        else:
            self.claudeai_api_key_save_button.setVisible(False)
            self.claudeai_api_key_change_button.setVisible(True)

        if self.gemini_api_key_status is False:
            self.gemini_api_key_save_button.setVisible(True)
            self.gemini_api_key_change_button.setVisible(False)
        else:
            self.gemini_api_key_save_button.setVisible(False)
            self.gemini_api_key_change_button.setVisible(True)

        return self.openai_api_key_status, self.claudeai_api_key_status, self.gemini_api_key_status

    def input_openai_api_key(self):
        if self.openai_api_key_input.text():
            self.openai_api_key_save_button.setEnabled(True)
        else:
            self.openai_api_key_save_button.setEnabled(False)

    def input_claudeai_api_key(self):
        if self.claudeai_api_key_input.text():
            self.claudeai_api_key_save_button.setEnabled(True)
        else:
            self.claudeai_api_key_save_button.setEnabled(False)

    def input_gemini_api_key(self):
        if self.gemini_api_key_input.text():
            self.gemini_api_key_save_button.setEnabled(True)
        else:
            self.gemini_api_key_save_button.setEnabled(False)

    def save_openai_api_key(self):
        if self.openai_api_key_input.text():
            self.config.save_configuration('openai_api_key', self.openai_api_key_input.text())
            self.openai_api_key_input.clear()
            self.check_api_keys()
            self.set_lang_text()
            self.refresh_ai_model_signal.emit(True)

    def save_claudeai_api_key(self):
        if self.claudeai_api_key_input.text():
            self.config.save_configuration('claudeai_api_key', self.claudeai_api_key_input.text())
            self.claudeai_api_key_input.clear()
            self.check_api_keys()
            self.set_lang_text()
            self.refresh_ai_model_signal.emit(True)

    def save_gemini_api_key(self):
        if self.gemini_api_key_input.text():
            self.config.save_configuration('gemini_api_key', self.gemini_api_key_input.text())
            self.gemini_api_key_input.clear()
            self.check_api_keys()
            self.set_lang_text()
            self.refresh_ai_model_signal.emit(True)

    def change_openai_api_key(self):
        self.openai_api_key_change_status = True
        self.openai_api_key_input.setEnabled(True)
        self.openai_api_key_save_button.setVisible(True)
        self.openai_api_key_change_button.setVisible(False)
        self.openai_api_key_save_button.setEnabled(False)
        self.set_lang_text_settings_api_keys()

    def change_claudeai_api_key(self):
        self.claudeai_api_key_change_status = True
        self.claudeai_api_key_input.setEnabled(True)
        self.claudeai_api_key_save_button.setVisible(True)
        self.claudeai_api_key_change_button.setVisible(False)
        self.claudeai_api_key_save_button.setEnabled(False)
        self.set_lang_text_settings_api_keys()

    def change_gemini_api_key(self):
        self.gemini_api_key_change_status = True
        self.gemini_api_key_input.setEnabled(True)
        self.gemini_api_key_save_button.setVisible(True)
        self.gemini_api_key_change_button.setVisible(False)
        self.gemini_api_key_save_button.setEnabled(False)
        self.set_lang_text_settings_api_keys()
