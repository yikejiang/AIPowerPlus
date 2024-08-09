import sys
import os
import datetime
import threading

from PySide6.QtCore import Qt, Slot, QUrl, Signal
from PySide6.QtGui import QFont, QIcon
from PySide6.QtWidgets import (QApplication, QTextEdit, QLabel, QPushButton, QVBoxLayout, QHBoxLayout, QWidget,
                               QComboBox, QCheckBox, QSplitter, QSizePolicy)
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput

from lehandler import ExpertProcess
from lelang import LELang
from leconfig import Config
from lesettings import LESettings


class MainWindow(QWidget):
    interface_language_index_signal = Signal(int)
    expert_language_index_signal = Signal(int)

    def __init__(self):
        super().__init__()

        # 加载模块
        self.config = Config()
        self.lang = LELang()

        # Logo
        if os.name == 'nt':
            logo_path = self.config.get_logo_path()
            if os.path.exists(logo_path):
                self.setWindowIcon(QIcon(logo_path))

        # 初始化变量
        self.expert_process = None

        if self.config.read_configuration('expert_mode').isdigit():
            self.expert_mode_index = int(self.config.read_configuration('expert_mode'))
            self.expert_mode = self.lang.get_expert_mode(self.expert_mode_index)
        else:
            self.expert_mode_index = 0
            self.expert_mode = 'translator_mode'

        if self.config.read_configuration('interface_language').isdigit():
            self.interface_language_index = int(self.config.read_configuration('interface_language'))
            self.interface_language = self.lang.get_interface_language(self.interface_language_index)
        else:
            self.interface_language_index = 0
            self.interface_language = 'English'

        self.settings = LESettings(self.interface_language_index, self.expert_mode_index)

        if self.config.read_configuration('translation_language').isdigit():
            self.translation_language_index = int(self.config.read_configuration('translation_language'))
            self.translation_language = self.lang.get_translation_language(self.translation_language_index)
        else:
            self.translation_language_index = 0
            self.translation_language = 'English'

        if self.config.read_configuration('tts_voice').isdigit():
            self.tts_voice_index = int(self.config.read_configuration('tts_voice'))
            self.tts_voice = self.lang.get_tts_voice(self.tts_voice_index)
        else:
            self.tts_voice_index = 0
            self.tts_voice = 'alloy'

        self.ai_model_index = 0
        self.ai_model = ''

        self.current_user_message = ''
        self.chat_context = ''

        self.player = QMediaPlayer()
        self.audio_output = QAudioOutput()
        self.player.setAudioOutput(self.audio_output)
        self.play_again_status = False

        self.ai_comments_status = True

        self.chat_context_status = False

        self.current_time = datetime.datetime.now()

        font = QFont()
        font.setPointSize(12)

        # 设置窗口大小
        screen = app.primaryScreen()
        self.screen_width = screen.availableSize().width()
        self.screen_height = screen.availableSize().height()

        window_width = 1200
        if self.screen_height < 1080:
            window_height = 920
        else:
            window_height = 1080
        window_x = int((self.screen_width - window_width) / 2)
        window_y = int((self.screen_height - window_height) / 2)

        self.setGeometry(window_x, window_y, window_width, window_height)

        # 总体布局
        self.layout = QVBoxLayout()
        self.layout.setAlignment(Qt.AlignmentFlag.AlignTop)
        self.setLayout(self.layout)

        # 顶部布局
        self.layout_top = QHBoxLayout()
        self.top_container = QWidget()
        self.top_container.setLayout(self.layout_top)

        self.layout.addWidget(self.top_container)

        self.layout_top_right = QHBoxLayout()
        self.layout_top_right.setAlignment(Qt.AlignmentFlag.AlignRight)
        self.layout_top.addLayout(self.layout_top_right)

        # 主要部件布局
        self.layout_main = QVBoxLayout()

        self.main_splitter = QSplitter()
        self.main_splitter.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
        self.main_splitter.setOrientation(Qt.Orientation.Horizontal)
        self.main_splitter.setLayout(self.layout_main)

        self.layout.addWidget(self.main_splitter)

        # 左右容器
        self.layout_main_left = QVBoxLayout()
        self.left_splitter = QSplitter()
        self.left_splitter.setOrientation(Qt.Orientation.Vertical)
        self.left_splitter.setLayout(self.layout_main_left)

        self.layout_main.addWidget(self.left_splitter)

        self.layout_main_right = QVBoxLayout()
        self.right_splitter = QSplitter()
        self.right_splitter.setOrientation(Qt.Orientation.Vertical)
        self.right_splitter.setLayout(self.layout_main_right)

        self.layout_main.addWidget(self.right_splitter)

        self.main_splitter.addWidget(self.left_splitter)
        self.main_splitter.addWidget(self.right_splitter)

        # 左侧主要部件布局
        self.layout_main_left_upper = QVBoxLayout()
        self.left_upper_container = QWidget()
        self.left_upper_container.setLayout(self.layout_main_left_upper)

        self.layout_main_left_lower = QVBoxLayout()
        self.left_lower_container = QWidget()
        self.left_lower_container.setLayout(self.layout_main_left_lower)

        self.left_splitter.addWidget(self.left_upper_container)
        self.left_splitter.addWidget(self.left_lower_container)

        # 右侧主要部件布局
        self.layout_main_right_upper = QVBoxLayout()
        self.right_upper_container = QWidget()
        self.right_upper_container.setLayout(self.layout_main_right_upper)

        self.layout_main_right_lower = QVBoxLayout()
        self.right_lower_container = QWidget()
        self.right_lower_container.setLayout(self.layout_main_right_lower)

        self.right_splitter.addWidget(self.right_upper_container)
        self.right_splitter.addWidget(self.right_lower_container)

        # 左侧顶部靠左部件布局
        self.layout_main_left_top = QHBoxLayout()
        self.layout_main_left_upper.addLayout(self.layout_main_left_top)

        self.layout_main_left_top_left = QHBoxLayout()
        self.layout_main_left_top_left.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_left_top.addLayout(self.layout_main_left_top_left)

        # 左侧顶部靠右部件布局
        self.layout_main_left_top_right = QHBoxLayout()
        self.layout_main_left_top_right.setAlignment(Qt.AlignmentFlag.AlignRight)
        self.layout_main_left_top.addLayout(self.layout_main_left_top_right)

        # 右侧顶部靠左布局
        self.layout_main_right_upper_top = QHBoxLayout()
        self.layout_main_right_upper.addLayout(self.layout_main_right_upper_top)

        self.layout_main_right_upper_top_left = QHBoxLayout()
        self.layout_main_right_upper_top_left.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_right_upper_top.addLayout(self.layout_main_right_upper_top_left)

        # 右侧顶部靠右布局
        self.layout_main_right_upper_top_right = QHBoxLayout()
        self.layout_main_right_upper_top_right.setAlignment(Qt.AlignmentFlag.AlignRight)
        self.layout_main_right_upper_top.addLayout(self.layout_main_right_upper_top_right)

        # 右侧下部顶部布局
        self.layout_main_right_lower_top = QHBoxLayout()
        self.layout_main_right_lower.addLayout(self.layout_main_right_lower_top)

        self.layout_main_right_lower_top_left = QHBoxLayout()
        self.layout_main_right_lower_top_left.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.layout_main_right_lower_top.addLayout(self.layout_main_right_lower_top_left)

        self.layout_main_right_lower_top_right = QHBoxLayout()
        self.layout_main_right_lower_top_right.setAlignment(Qt.AlignmentFlag.AlignRight)
        self.layout_main_right_lower_top.addLayout(self.layout_main_right_lower_top_right)

        # 顶部设置
        self.expert_mode_label = QLabel()
        self.expert_mode_label.setFixedHeight(30)
        self.layout_top_right.addWidget(self.expert_mode_label)

        self.expert_mode_chooser = QComboBox()
        self.expert_mode_chooser.setFixedWidth(150)
        self.expert_mode_chooser.addItems(self.lang.expert_mode)
        self.expert_mode_chooser.setCurrentIndex(self.expert_mode_index)
        self.layout_top_right.addWidget(self.expert_mode_chooser)

        self.interface_language_label = QLabel()
        self.layout_top_right.addWidget(self.interface_language_label)

        self.interface_language_chooser = QComboBox()
        self.interface_language_chooser.setFixedWidth(90)
        self.interface_language_chooser.addItems(self.lang.interface_language)
        self.interface_language_chooser.setCurrentIndex(self.interface_language_index)
        self.layout_top_right.addWidget(self.interface_language_chooser)

        self.ai_model_label = QLabel()
        self.layout_top_right.addWidget(self.ai_model_label)

        self.ai_model_chooser = QComboBox()
        self.ai_model_chooser.setFixedWidth(180)
        self.layout_top_right.addWidget(self.ai_model_chooser)

        self.settings_button = QPushButton()
        self.settings_button.setFixedWidth(90)
        self.layout_top_right.addWidget(self.settings_button)

        # 用户文本输入区域
        self.user_text_label = QLabel()
        self.user_text_label.setFixedHeight(30)
        self.layout_main_left_top_left.addWidget(self.user_text_label)

        self.tts_voice_label = QLabel()
        self.layout_main_left_top_left.addWidget(self.tts_voice_label)

        self.tts_voice_chooser = QComboBox()
        self.tts_voice_chooser.setFixedWidth(90)
        self.tts_voice_chooser.addItems(self.lang.tts_voice_name)
        self.tts_voice_chooser.setCurrentIndex(self.tts_voice_index)
        self.layout_main_left_top_left.addWidget(self.tts_voice_chooser)

        self.process_button = QPushButton()
        self.process_button.setFixedWidth(90)
        self.process_button.setEnabled(False)
        self.layout_main_left_top_left.addWidget(self.process_button)

        self.play_audio_button = QPushButton()
        self.play_audio_button.setFixedWidth(90)
        self.play_audio_button.setEnabled(False)
        self.layout_main_left_top_right.addWidget(self.play_audio_button)

        self.translation_language_label = QLabel()
        self.layout_main_left_top_right.addWidget(self.translation_language_label)

        self.translation_language_chooser = QComboBox()
        self.translation_language_chooser.setFixedWidth(90)
        self.translation_language_chooser.addItems(self.lang.translation_language)
        self.translation_language_chooser.setCurrentIndex(self.translation_language_index)
        self.layout_main_left_top_right.addWidget(self.translation_language_chooser)

        self.user_text = QTextEdit()
        self.user_text.setAcceptRichText(False)
        self.user_text.setFont(font)
        self.layout_main_left_upper.addWidget(self.user_text)

        # AI 文本显示区域
        self.ai_text_label = QLabel()
        self.ai_text_label.setFixedHeight(30)
        self.layout_main_left_lower.addWidget(self.ai_text_label)

        self.ai_text = QTextEdit()
        self.ai_text.setAcceptRichText(False)
        self.ai_text.setFont(font)
        self.layout_main_left_lower.addWidget(self.ai_text)

        # 用户评论区域
        self.user_message_label = QLabel()
        self.user_message_label.setFixedHeight(30)
        self.layout_main_right_upper_top_left.addWidget(self.user_message_label)

        self.chat_context_option_label = QLabel()
        self.layout_main_right_upper_top_right.addWidget(self.chat_context_option_label)

        self.chat_context_option = QCheckBox()
        self.chat_context_option.setChecked(False)
        self.chat_context_option.checkStateChanged.connect(self.set_chat_context_option)
        self.layout_main_right_upper_top_right.addWidget(self.chat_context_option)

        self.submit_button = QPushButton()
        self.submit_button.setFixedWidth(90)
        self.submit_button.setEnabled(False)
        self.layout_main_right_upper_top_right.addWidget(self.submit_button)

        self.user_message = QTextEdit()
        self.user_message.setAcceptRichText(False)
        self.user_message.setFont(font)
        self.layout_main_right_upper.addWidget(self.user_message)

        # AI 解释
        self.ai_comments_label = QLabel()
        self.ai_comments_label.setVisible(False)
        self.ai_comments_label.setFixedHeight(30)
        self.layout_main_right_lower_top_left.addWidget(self.ai_comments_label)

        # 聊天历史
        self.chat_history_label = QLabel()
        self.chat_history_label.setFixedHeight(30)
        self.layout_main_right_lower_top_left.addWidget(self.chat_history_label)

        self.ai_comments_and_chat_history_switch_button = QPushButton()
        self.ai_comments_and_chat_history_switch_button.setFixedWidth(120)
        self.layout_main_right_lower_top_left.addWidget(self.ai_comments_and_chat_history_switch_button)

        self.clear_chat_history_button = QPushButton()
        self.clear_chat_history_button.setVisible(False)
        self.clear_chat_history_button.setFixedWidth(100)
        self.layout_main_right_lower_top_right.addWidget(self.clear_chat_history_button)

        self.ai_comments_text = QTextEdit()
        self.ai_comments_text.setVisible(False)
        self.ai_comments_text.setFont(font)
        self.ai_comments_text.setReadOnly(True)
        self.layout_main_right_lower.addWidget(self.ai_comments_text)

        self.chat_history = QTextEdit()
        self.chat_history.setReadOnly(True)
        self.chat_history.setFont(font)
        self.layout_main_right_lower.addWidget(self.chat_history)

        # 教师模式
        self.blackboard_label = QLabel()
        self.blackboard_label.setFixedHeight(30)
        self.blackboard_label.setVisible(False)
        self.layout_main_left_top.addWidget(self.blackboard_label)

        self.blackboard_text = QTextEdit()
        self.blackboard_text.setVisible(False)
        self.blackboard_text.setFont(font)
        self.blackboard_text.setReadOnly(True)
        self.layout_main_left_upper.addWidget(self.blackboard_text)

        self.teacher_explanation_label = QLabel()
        self.teacher_explanation_label.setFixedHeight(30)
        self.layout_main_left_lower.addWidget(self.teacher_explanation_label)

        self.teacher_explanation_text = QTextEdit()
        self.teacher_explanation_text.setVisible(False)
        self.teacher_explanation_text.setFont(font)
        self.teacher_explanation_text.setReadOnly(True)
        self.layout_main_left_lower.addWidget(self.teacher_explanation_text)

        # 启动执行
        self.refresh_ai_model_list()
        self.adjust_expert_interface()
        self.set_lang_text()

        self.interface_language_index_signal.connect(self.settings.change_interface_language_index)
        self.expert_language_index_signal.connect(self.settings.change_expert_mode_index)

        # 信号发射
        # 功能区
        self.expert_mode_chooser.currentIndexChanged.connect(self.change_expert_mode)
        self.interface_language_chooser.currentIndexChanged.connect(self.change_interface_language)
        self.ai_model_chooser.currentIndexChanged.connect(self.change_ai_model)
        self.settings_button.clicked.connect(self.change_settings)
        self.translation_language_chooser.currentIndexChanged.connect(self.change_translation_language)
        self.tts_voice_chooser.currentIndexChanged.connect(self.change_tts_voice)
        self.process_button.clicked.connect(self.process_text)
        self.play_audio_button.clicked.connect(self.play_audio)
        self.user_text.textChanged.connect(self.when_user_text_is_changed)
        self.submit_button.clicked.connect(self.submit)
        self.user_message.textChanged.connect(self.when_user_message_is_changed)
        self.ai_comments_and_chat_history_switch_button.clicked.connect(self.switch_ai_comments_or_chat_history)
        self.clear_chat_history_button.clicked.connect(self.clear_chat_history)

        self.settings.refresh_ai_model_signal.connect(self.refresh_ai_model_list)

    @Slot()
    def change_settings(self):
        x, y = self.get_current_geometry()

        self.settings.move(x, y)
        self.settings.show()

    @Slot()
    def change_expert_mode(self, index):
        self.config.save_configuration('expert_mode', index)

        self.expert_mode_index = index
        self.expert_mode = self.lang.get_expert_mode(index)

        self.expert_language_index_signal.emit(index)

        self.adjust_expert_interface()

    @Slot()
    def change_interface_language(self, index):
        self.config.save_configuration('interface_language', index)

        self.interface_language_index = index
        self.interface_language = self.lang.get_interface_language(index)

        self.interface_language_index_signal.emit(index)

        self.set_lang_text()

    @Slot()
    def change_ai_model(self, index):
        self.config.save_configuration('ai_model', index)

        self.ai_model_index = index
        self.ai_model = self.config.get_ai_model(index)

        self.set_lang_text()

    @Slot()
    def change_translation_language(self, index):
        self.config.save_configuration('translation_language', index)

        self.translation_language_index = index
        self.translation_language = self.lang.get_translation_language(index)

    @Slot()
    def change_tts_voice(self, index):
        self.config.save_configuration('tts_voice', index)

        self.tts_voice_index = index
        self.tts_voice = self.lang.get_tts_voice(index)

    @Slot()
    def play_audio(self):
        gpt_audio_path = self.config.read_gpt_audio_path()

        if os.path.exists(gpt_audio_path):
            self.player.setSource(QUrl.fromLocalFile(gpt_audio_path))
            play_audio_thread = threading.Thread(target=self.play_audio_thread)
            play_audio_thread.start()
            self.play_audio_button.setText(self.lang.get_lang(self.interface_language_index,'play_again'))
            self.play_again_status = True

    def get_current_geometry(self):
        x = self.geometry().x()
        y = self.geometry().y()
        width = self.geometry().width()
        height = self.geometry().height()

        right_x = x + width

        settings_x = int(x + (width - 800) / 2)
        settings_y = int(y + (height - 600) / 2)

        return settings_x, settings_y

    def play_audio_thread(self):
        self.player.play()

    @Slot()
    def when_user_text_is_changed(self):
        self.reset_submit_button_status()

    @Slot()
    def when_user_message_is_changed(self):
        self.reset_submit_button_status()

    @Slot()
    def set_chat_context_option(self):
        if self.chat_context_option.isChecked():
            self.chat_context_status = True
        else:
            self.chat_context_status = False

    @Slot()
    def process_text(self):
        self.process_button.setEnabled(False)
        self.process_request()

    @Slot()
    def submit(self):
        self.chat_context = self.chat_history.toPlainText()

        self.current_user_message = self.user_message.toPlainText()

        if self.chat_history.toPlainText():
            self.chat_history.append('\n')

        self.chat_history.append(f'USER ({self.current_time}):\n\n'
                                 f'{self.current_user_message}')

        self.process_request()

    @Slot()
    def switch_ai_comments_or_chat_history(self):
        if self.ai_comments_status is False:
            self.ai_comments_label.setVisible(True)
            self.ai_comments_text.setVisible(True)
            self.chat_history_label.setVisible(False)
            self.chat_history.setVisible(False)
            self.clear_chat_history_button.setVisible(False)
            self.ai_comments_status = True
        else:
            self.ai_comments_label.setVisible(False)
            self.ai_comments_text.setVisible(False)
            self.chat_history_label.setVisible(True)
            self.chat_history.setVisible(True)
            self.clear_chat_history_button.setVisible(True)
            self.ai_comments_status = False

        self.set_lang_text()

    @Slot()
    def clear_chat_history(self):
        self.chat_history.clear()

    @Slot()
    def process_result(self, ai_text, ai_comments, ai_reply):
        if ai_text:
            if self.expert_mode == 'teacher_mode':
                self.blackboard_text.setText(ai_text)
            else:
                self.ai_text.setText(ai_text)

        if ai_comments:
            if self.expert_mode == 'teacher_mode':
                self.teacher_explanation_text.setText(ai_comments)

            if self.expert_mode == 'translator_mode' or self.expert_mode == 'writing_helper_mode' or self.expert_mode == 'writer_mode':
                self.ai_comments_text.setText(ai_comments)

            if self.chat_history.toPlainText():
                self.chat_history.append('\n')

            self.chat_history.append(f'AI ({self.current_time}):\n\n'
                                     f'{ai_reply}')

        if self.expert_mode == 'speaker_mode':
            gpt_audio_path = self.config.read_gpt_audio_path()
            if os.path.exists(gpt_audio_path):
                self.play_audio_button.setEnabled(True)
                self.play_audio_button.setText(self.lang.get_lang(self.interface_language_index, 'play_audio'))
                self.player.setSource(QUrl())
                self.play_again_status = False

        self.process_button.setEnabled(True)
        self.submit_button.setEnabled(True)

    def refresh_ai_model_list(self):
        openai_api_key_status, claudeai_api_key_status, gemini_api_key_status = self.settings.check_api_keys()
        ai_model_custom_names, ai_model_names = self.config.read_ai_models()

        available_ai_model_names = []
        available_ai_model_custom_names = []

        for item in ai_model_names:
            if openai_api_key_status:
                if 'gpt' in item:
                    available_ai_model_names.append(item)
                    item_index = ai_model_names.index(item)
                    available_ai_model_custom_names.append(ai_model_custom_names[item_index])

            if claudeai_api_key_status:
                if 'claude' in item:
                    available_ai_model_names.append(item)
                    item_index = ai_model_names.index(item)
                    available_ai_model_custom_names.append(ai_model_custom_names[item_index])

            if gemini_api_key_status:
                if 'gemini' in item:
                    available_ai_model_names.append(item)
                    item_index = ai_model_names.index(item)
                    available_ai_model_custom_names.append(ai_model_custom_names[item_index])

        if self.config.read_configuration('ai_model').isdigit():
            if int(self.config.read_configuration('ai_model')) < len(available_ai_model_names):
                self.ai_model_index = int(self.config.read_configuration('ai_model'))

        if available_ai_model_custom_names:
            self.ai_model = available_ai_model_names[self.ai_model_index]

        self.ai_model_chooser.clear()
        self.ai_model_chooser.addItems(available_ai_model_custom_names)
        self.ai_model_chooser.setCurrentIndex(self.ai_model_index)

        self.adjust_expert_interface()

    def reset_submit_button_status(self):
        user_text = self.user_text.toPlainText()

        if self.expert_mode == 'translator_mode' or self.expert_mode == 'writing_helper_mode' or self.expert_mode == 'writer_mode':
            if user_text:
                self.submit_button.setEnabled(True)
            else:
                self.submit_button.setEnabled(False)

        user_message = self.user_message.toPlainText()

        if self.expert_mode == 'teacher_mode' or self.expert_mode == 'programmer_mode' or self.expert_mode == 'free_mode':
            if user_message:
                self.submit_button.setEnabled(True)
            else:
                self.submit_button.setEnabled(False)

        if self.expert_mode == 'speaker_mode':
            if user_text:
                self.process_button.setEnabled(True)
            else:
                self.process_button.setEnabled(False)

    def adjust_expert_interface(self):
        if self.expert_mode == 'translator_mode':
            self.left_splitter.setSizes(
                [int(self.main_splitter.height() * 0.4), int(self.main_splitter.height() * 0.6)])
            self.right_splitter.setSizes(
                [int(self.main_splitter.height() * 0.3), int(self.main_splitter.height() * 0.7)])
            self.main_splitter.setSizes([int(self.main_splitter.width() * 0.55), int(self.main_splitter.width() * 0.45)])

            self.user_text_label.setVisible(True)
            self.user_text.setVisible(True)

            self.translation_language_label.setVisible(True)
            self.translation_language_chooser.setVisible(True)

            self.tts_voice_label.setVisible(False)
            self.tts_voice_chooser.setVisible(False)
            self.process_button.setVisible(False)
            self.play_audio_button.setVisible(False)

            self.ai_text_label.setVisible(True)
            self.ai_text.setVisible(True)

            self.blackboard_label.setVisible(False)
            self.blackboard_text.setVisible(False)
            self.teacher_explanation_label.setVisible(False)
            self.teacher_explanation_text.setVisible(False)

            self.user_message_label.setVisible(True)
            self.user_message.setVisible(True)

            self.chat_context_option_label.setVisible(True)
            self.chat_context_option.setVisible(True)

            self.submit_button.setVisible(True)

            self.ai_comments_and_chat_history_switch_button.setVisible(True)

            if self.ai_comments_status:
                self.clear_chat_history_button.setVisible(False)
                self.ai_comments_label.setVisible(True)
                self.ai_comments_text.setVisible(True)
                self.chat_history_label.setVisible(False)
                self.chat_history.setVisible(False)
            else:
                self.clear_chat_history_button.setVisible(True)
                self.ai_comments_label.setVisible(False)
                self.ai_comments_text.setVisible(False)
                self.chat_history_label.setVisible(True)
                self.chat_history.setVisible(True)

        if self.expert_mode == 'writing_helper_mode' or self.expert_mode == 'writer_mode':
            self.left_splitter.setSizes(
                [int(self.main_splitter.height() * 0.4), int(self.main_splitter.height() * 0.6)])
            self.right_splitter.setSizes(
                [int(self.main_splitter.height() * 0.3), int(self.main_splitter.height() * 0.7)])
            self.main_splitter.setSizes([int(self.main_splitter.width() * 0.55), int(self.main_splitter.width() * 0.45)])

            self.user_text_label.setVisible(True)
            self.user_text.setVisible(True)

            self.translation_language_label.setVisible(False)
            self.translation_language_chooser.setVisible(False)

            self.tts_voice_label.setVisible(False)
            self.tts_voice_chooser.setVisible(False)
            self.process_button.setVisible(False)
            self.play_audio_button.setVisible(False)

            self.ai_text_label.setVisible(True)
            self.ai_text.setVisible(True)

            self.blackboard_label.setVisible(False)
            self.blackboard_text.setVisible(False)
            self.teacher_explanation_label.setVisible(False)
            self.teacher_explanation_text.setVisible(False)

            self.user_message_label.setVisible(True)
            self.user_message.setVisible(True)

            self.chat_context_option_label.setVisible(True)
            self.chat_context_option.setVisible(True)

            self.submit_button.setVisible(True)

            self.ai_comments_and_chat_history_switch_button.setVisible(True)

            self.clear_chat_history_button.setEnabled(True)

            if self.ai_comments_status:
                self.clear_chat_history_button.setVisible(False)
                self.ai_comments_label.setVisible(True)
                self.ai_comments_text.setVisible(True)
                self.chat_history_label.setVisible(False)
                self.chat_history.setVisible(False)
            else:
                self.clear_chat_history_button.setVisible(True)
                self.ai_comments_label.setVisible(False)
                self.ai_comments_text.setVisible(False)
                self.chat_history_label.setVisible(True)
                self.chat_history.setVisible(True)

        if self.expert_mode == 'teacher_mode':
            self.left_splitter.setSizes([int(self.main_splitter.height() * 0.4), int(self.main_splitter.height() * 0.6)])
            self.right_splitter.setSizes([int(self.main_splitter.height() * 0.3), int(self.main_splitter.height() * 0.7)])
            self.main_splitter.setSizes([int(self.main_splitter.width() * 0.6), int(self.main_splitter.width() * 0.4)])

            self.user_text_label.setVisible(False)
            self.user_text.setVisible(False)

            self.translation_language_label.setVisible(False)
            self.translation_language_chooser.setVisible(False)

            self.tts_voice_label.setVisible(False)
            self.tts_voice_chooser.setVisible(False)
            self.process_button.setVisible(False)
            self.play_audio_button.setVisible(False)

            self.ai_text_label.setVisible(False)
            self.ai_text.setVisible(False)

            self.blackboard_label.setVisible(True)
            self.blackboard_text.setVisible(True)
            self.teacher_explanation_label.setVisible(True)
            self.teacher_explanation_text.setVisible(True)

            self.user_message_label.setVisible(True)
            self.user_message.setVisible(True)

            self.chat_context_option_label.setVisible(True)
            self.chat_context_option.setVisible(True)

            self.submit_button.setVisible(True)

            self.ai_comments_and_chat_history_switch_button.setVisible(False)

            self.clear_chat_history_button.setVisible(True)

            self.ai_comments_label.setVisible(False)
            self.ai_comments_text.setVisible(False)
            self.chat_history_label.setVisible(True)
            self.chat_history.setVisible(True)

        if self.expert_mode == 'programmer_mode' or self.expert_mode == 'free_mode':
            self.main_splitter.setSizes([0, self.main_splitter.width()])
            self.right_splitter.setSizes([int(self.main_splitter.height() * 0.2), int(self.main_splitter.height() * 0.8)])

            self.user_text_label.setVisible(False)
            self.user_text.setVisible(False)

            self.translation_language_label.setVisible(False)
            self.translation_language_chooser.setVisible(False)

            self.tts_voice_label.setVisible(False)
            self.tts_voice_chooser.setVisible(False)
            self.process_button.setVisible(False)
            self.play_audio_button.setVisible(False)

            self.ai_text_label.setVisible(False)
            self.ai_text.setVisible(False)

            self.blackboard_label.setVisible(False)
            self.blackboard_text.setVisible(False)
            self.teacher_explanation_label.setVisible(False)
            self.teacher_explanation_text.setVisible(False)

            self.user_message_label.setVisible(True)
            self.user_message.setVisible(True)

            self.chat_context_option_label.setVisible(True)
            self.chat_context_option.setVisible(True)

            self.submit_button.setVisible(True)

            self.ai_comments_and_chat_history_switch_button.setVisible(False)

            self.clear_chat_history_button.setVisible(True)

            self.ai_comments_label.setVisible(False)
            self.ai_comments_text.setVisible(False)
            self.chat_history_label.setVisible(True)
            self.chat_history.setVisible(True)

        if self.expert_mode == 'speaker_mode':
            self.left_splitter.setSizes([self.main_splitter.height(), 0])
            self.main_splitter.setSizes([self.main_splitter.width(), 0])

            self.user_text_label.setVisible(True)
            self.user_text.setVisible(True)

            self.translation_language_label.setVisible(False)
            self.translation_language_chooser.setVisible(False)

            self.tts_voice_label.setVisible(True)
            self.tts_voice_chooser.setVisible(True)
            self.process_button.setVisible(True)
            self.play_audio_button.setVisible(True)

            self.ai_text_label.setVisible(False)
            self.ai_text.setVisible(False)

            self.blackboard_label.setVisible(False)
            self.blackboard_text.setVisible(False)
            self.teacher_explanation_label.setVisible(False)
            self.teacher_explanation_text.setVisible(False)

            self.user_message_label.setVisible(False)
            self.user_message.setVisible(False)

            self.chat_context_option_label.setVisible(False)
            self.chat_context_option.setVisible(False)

            self.submit_button.setVisible(False)

            self.ai_comments_and_chat_history_switch_button.setVisible(False)

            self.clear_chat_history_button.setVisible(False)

            self.ai_comments_label.setVisible(False)
            self.ai_comments_text.setVisible(False)
            self.chat_history_label.setVisible(False)
            self.chat_history.setVisible(False)

        self.reset_submit_button_status()

        if self.ai_model == '':
            self.user_text.setEnabled(False)
            self.process_button.setEnabled(False)
            self.play_audio_button.setEnabled(False)
            self.ai_text.setEnabled(False)
            self.user_message.setEnabled(False)
            self.chat_context_option.setEnabled(False)
            self.submit_button.setEnabled(False)
            self.ai_comments_and_chat_history_switch_button.setEnabled(False)
            self.clear_chat_history_button.setEnabled(False)
            self.ai_comments_text.setEnabled(False)
            self.chat_history.setEnabled(False)
            self.blackboard_text.setEnabled(False)
            self.teacher_explanation_text.setEnabled(False)
        else:
            self.user_text.setEnabled(True)
            self.ai_text.setEnabled(True)
            self.user_message.setEnabled(True)
            self.chat_context_option.setEnabled(True)
            self.submit_button.setEnabled(True)
            self.ai_comments_and_chat_history_switch_button.setEnabled(True)
            self.clear_chat_history_button.setEnabled(True)
            self.ai_comments_text.setEnabled(True)
            self.chat_history.setEnabled(True)
            self.blackboard_text.setEnabled(True)
            self.teacher_explanation_text.setEnabled(True)

            openai_api_key_status, _, _ = self.settings.check_api_keys()
            if openai_api_key_status:
                self.process_button.setEnabled(True)
                self.play_audio_button.setEnabled(True)
            else:
                self.process_button.setEnabled(False)
                self.play_audio_button.setEnabled(False)

    def process_request(self):
        self.submit_button.setEnabled(False)
        self.process_button.setEnabled(False)

        user_text = self.user_text.toPlainText()
        user_message = self.user_message.toPlainText()

        self.expert_process = ExpertProcess(self.expert_mode, self.interface_language, self.translation_language,
                                            user_text, user_message, self.chat_context_status, self.chat_context,
                                            self.ai_model, self.tts_voice)
        self.expert_process.expert_process_done.connect(self.process_result)
        self.expert_process.start()

    def set_lang_text(self):
        # 功能区
        self.setWindowTitle(self.lang.get_lang(self.interface_language_index, 'app_name'))

        self.expert_mode_label.setText(self.lang.get_lang(self.interface_language_index, 'expert_mode'))

        self.expert_mode_chooser.setItemText(0, self.lang.get_lang(self.interface_language_index, 'translator_mode'))
        self.expert_mode_chooser.setItemText(1,
                                             self.lang.get_lang(self.interface_language_index, 'writing_helper_mode'))
        self.expert_mode_chooser.setItemText(2, self.lang.get_lang(self.interface_language_index, 'writer_mode'))
        self.expert_mode_chooser.setItemText(3, self.lang.get_lang(self.interface_language_index, 'teacher_mode'))
        self.expert_mode_chooser.setItemText(4, self.lang.get_lang(self.interface_language_index, 'programmer_mode'))
        self.expert_mode_chooser.setItemText(5, self.lang.get_lang(self.interface_language_index, 'free_mode'))
        self.expert_mode_chooser.setItemText(6, self.lang.get_lang(self.interface_language_index, 'speaker_mode'))

        self.interface_language_label.setText(
            self.lang.get_lang(self.interface_language_index, 'interface_language'))

        self.ai_model_label.setText(self.lang.get_lang(self.interface_language_index, 'ai_model'))

        self.user_text_label.setText(self.lang.get_lang(self.interface_language_index, 'user_text'))

        self.process_button.setText(self.lang.get_lang(self.interface_language_index, 'process'))

        self.translation_language_label.setText(self.lang.get_lang(self.interface_language_index, 'translation_language'))

        self.tts_voice_label.setText(self.lang.get_lang(self.interface_language_index, 'tts_voice'))

        if self.play_again_status is False:
            self.play_audio_button.setText(self.lang.get_lang(self.interface_language_index, 'play_audio'))
        else:
            self.play_audio_button.setText(self.lang.get_lang(self.interface_language_index, 'play_again'))

        self.ai_text_label.setText(self.lang.get_lang(self.interface_language_index, 'ai_text_label'))

        self.settings_button.setText(self.lang.get_lang(self.interface_language_index, 'settings'))

        self.user_message_label.setText(self.lang.get_lang(self.interface_language_index, 'user_message_label'))

        self.chat_context_option_label.setText(self.lang.get_lang(self.interface_language_index, 'chat_context_option'))

        self.submit_button.setText(self.lang.get_lang(self.interface_language_index, 'submit_button'))

        self.ai_comments_label.setText(self.lang.get_lang(self.interface_language_index, 'explanation'))

        if self.ai_comments_status:
            self.ai_comments_and_chat_history_switch_button.setText(self.lang.get_lang(self.interface_language_index, 'show_chat_history'))
        else:
            self.ai_comments_and_chat_history_switch_button.setText(
                self.lang.get_lang(self.interface_language_index, 'show_ai_comments'))

        self.clear_chat_history_button.setText(self.lang.get_lang(self.interface_language_index, 'clear'))

        self.chat_history_label.setText(self.lang.get_lang(self.interface_language_index, 'chat_history'))

        self.blackboard_label.setText(self.lang.get_lang(self.interface_language_index, 'blackboard'))
        self.teacher_explanation_label.setText(self.lang.get_lang(self.interface_language_index, 'explanation'))

    def closeEvent(self, event):
        self.player.setSource(QUrl())
        self.config.remove_temp_folder()


if __name__ == "__main__":
    app = QApplication([])
    translator = MainWindow()
    translator.show()
    sys.exit(app.exec())


