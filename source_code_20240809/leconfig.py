import sys
import os
import shutil


class Config:
    def __init__(self):
        super(Config, self).__init__()

    @staticmethod
    def get_app_folder_path():
        app_folder_path = os.path.dirname(sys.argv[0])
        return app_folder_path

    def get_logo_path(self):
        app_folder_path = self.get_app_folder_path()
        logo_path = os.path.join(app_folder_path, 'logo.ico')
        return logo_path

    @staticmethod
    def read_profile_folder_path():
        if os.name == 'nt':
            profile_path = os.path.join(os.environ['LOCALAPPDATA'], 'AIPowerPlus')
        elif sys.platform == 'darwin':
            profile_path = os.path.join(os.environ['HOME'], '.AIPowerPlus')
        else:
            profile_path = os.path.join(os.environ['HOME'], '.config/AIPowerPlus')

        profile_path = os.path.normpath(profile_path)

        if os.path.exists(profile_path) is False:
            os.mkdir(profile_path)

        return profile_path

    def read_app_configuration_path(self):
        profile_folder_path = self.read_profile_folder_path()
        app_configuration_path = os.path.join(profile_folder_path, 'AIPowerPlus.ini')

        if os.path.exists(app_configuration_path) is False:
            with open(app_configuration_path, 'w') as f:
                f.write('')

        return app_configuration_path

    def read_configuration(self, configuration_entry):
        app_configuration_path = self.read_app_configuration_path()
        configuration_value = ''

        with open(app_configuration_path, 'r') as f:
            for line in f.readlines():
                line = line.strip(' \n')
                parameter = line.split('=')
                if parameter[0].strip() == configuration_entry:
                    configuration_value = parameter[1].strip()

        return configuration_value

    def save_configuration(self, configuration_entry, configuration_value):
        app_configuration_path = self.read_app_configuration_path()

        line_number = 1
        configuration_entry_index = 0
        new_configuration_lines = []

        with open(app_configuration_path, 'r') as f:
            configuration_lines = f.readlines()
            count_lines = len(configuration_lines)

            if count_lines > 0:
                for line in configuration_lines:
                    line = line.strip(' \n')
                    if line:
                        new_configuration_lines.append(line + '\n')

                for line in new_configuration_lines:
                    parameter = line.split('=')
                    if parameter[0].strip() == configuration_entry:
                        configuration_entry_index = line_number

                    line_number = line_number + 1

        if count_lines == 0 or configuration_entry_index == 0:
            new_configuration_lines.append(f'{configuration_entry} = {configuration_value}' + '\n')
        else:
            new_configuration_lines[configuration_entry_index - 1] = f'{configuration_entry} = {configuration_value}' + '\n'

        with open(app_configuration_path, 'w') as f:
            f.writelines(new_configuration_lines)

    def add_ai_model(self, ai_model_custom_name, ai_model_name):
        ai_model_custom_names = self.read_configuration('ai_model_custom_names')
        ai_model_names = self.read_configuration('ai_model_names')

        if ai_model_custom_names:
            ai_model_custom_names = ai_model_custom_names + ',' + ai_model_custom_name
        else:
            ai_model_custom_names = ai_model_custom_name

        if ai_model_names:
            ai_model_names = ai_model_names + ',' + ai_model_name
        else:
            ai_model_names = ai_model_name

        self.save_configuration('ai_model_custom_names', ai_model_custom_names)
        self.save_configuration('ai_model_names', ai_model_names)

    def read_ai_models(self):
        ai_model_custom_names = self.read_configuration('ai_model_custom_names')
        ai_model_names = self.read_configuration('ai_model_names')

        if ai_model_custom_names:
            ai_model_custom_names = ai_model_custom_names.split(',')
        else:
            ai_model_custom_names = []

        if ai_model_names:
            ai_model_names = ai_model_names.split(',')
        else:
            ai_model_names = []

        return ai_model_custom_names, ai_model_names

    def get_ai_model(self, index):
        _, ai_model_names = self.read_ai_models()
        ai_model = ai_model_names[index]
        return ai_model

    def modify_ai_model(self, index, ai_model_custom_name, ai_model_name):
        ai_model_custom_names, ai_model_names = self.read_ai_models()
        ai_model_custom_names[index] = ai_model_custom_name
        ai_model_names[index] = ai_model_name
        ai_model_custom_names = ','.join(ai_model_custom_names)
        ai_model_names = ','.join(ai_model_names)
        self.save_configuration('ai_model_custom_names', ai_model_custom_names)
        self.save_configuration('ai_model_names', ai_model_names)

    def remove_ai_model(self, index):
        ai_model_custom_names, ai_model_names = self.read_ai_models()
        del ai_model_custom_names[index]
        del ai_model_names[index]
        ai_model_custom_names = ','.join(ai_model_custom_names)
        ai_model_names = ','.join(ai_model_names)
        self.save_configuration('ai_model_custom_names', ai_model_custom_names)
        self.save_configuration('ai_model_names', ai_model_names)

    def read_expert_mode_config_path(self, expert_mode_entry):
        profile_folder_path = self.read_profile_folder_path()
        expert_mode_config_ini_path = os.path.join(profile_folder_path, f'{expert_mode_entry}_config.ini')

        if os.path.exists(expert_mode_config_ini_path) is False:
            with open(expert_mode_config_ini_path, 'w') as f:
                f.write('')

        return expert_mode_config_ini_path

    def save_expert_mode_config(self, expert_mode_entry, config_entry, config_value):
        expert_mode_config_ini_path = self.read_expert_mode_config_path(expert_mode_entry)

        line_number = 1
        configuration_entry_index = 0
        new_configuration_lines = []

        with open(expert_mode_config_ini_path, 'r') as f:
            configuration_lines = f.readlines()
            count_lines = len(configuration_lines)

            if count_lines > 0:
                for line in configuration_lines:
                    line = line.strip(' \n')
                    if line:
                        new_configuration_lines.append(line + '\n')

                for line in new_configuration_lines:
                    parameter = line.split('=')
                    if parameter[0].strip() == config_entry:
                        configuration_entry_index = line_number

                    line_number = line_number + 1

        if count_lines == 0 or configuration_entry_index == 0:
            new_configuration_lines.append(f'{config_entry} = {config_value}' + '\n')
        else:
            new_configuration_lines[
                configuration_entry_index - 1] = f'{config_entry} = {config_value}' + '\n'

        with open(expert_mode_config_ini_path, 'w') as f:
            f.writelines(new_configuration_lines)

    def read_expert_mode_config(self, expert_mode_entry, config_entry):
        expert_mode_config_ini_path = self.read_expert_mode_config_path(expert_mode_entry)

        config_value = ''

        with open(expert_mode_config_ini_path, 'r') as f:
            for line in f.readlines():
                line = line.strip(' \n')
                parameter = line.split('=')
                if parameter[0].strip() == config_entry:
                    config_value = parameter[1].strip()

        return config_value

    def read_expert_mode_guidelines_path(self, expert_mode_entry):
        profile_folder_path = self.read_profile_folder_path()
        expert_role_ini_path = os.path.join(profile_folder_path, f'{expert_mode_entry}_role.ini')
        expert_requirements_ini_path = os.path.join(profile_folder_path, f'{expert_mode_entry}_requirements.ini')

        if os.path.exists(expert_role_ini_path) is False:
            with open(expert_role_ini_path, 'w') as f:
                f.write('')

        if os.path.exists(expert_requirements_ini_path) is False:
            with open(expert_requirements_ini_path, 'w') as f:
                f.write('')

        return expert_role_ini_path, expert_requirements_ini_path

    def read_expert_mode_guidelines(self, expert_mode_entry):
        expert_role_ini_path, expert_requirements_ini_path = self.read_expert_mode_guidelines_path(expert_mode_entry)

        with open(expert_role_ini_path, 'r') as f:
            expert_role = f.readlines()

        with open(expert_requirements_ini_path, 'r') as f:
            expert_requirements = f.readlines()

        return expert_role, expert_requirements

    def save_expert_mode_guidelines(self, expert_mode_entry, guidelines_type, guidelines_value):
        expert_role_ini_path, expert_requirements_ini_path = self.read_expert_mode_guidelines_path(expert_mode_entry)

        save_path = ''

        if guidelines_type == 'role':
            save_path = expert_role_ini_path

        if guidelines_type == 'requirements':
            save_path = expert_requirements_ini_path

        if save_path:
            with open(save_path, 'w') as f:
                f.writelines(guidelines_value)

    def read_temp_folder_path(self):
        profile_folder_path = self.read_profile_folder_path()
        temp_folder_path = os.path.join(profile_folder_path, 'temp')
        if os.path.exists(temp_folder_path) is False:
            os.mkdir(temp_folder_path)
        return temp_folder_path

    def remove_temp_folder(self):
        temp_folder_path = self.read_temp_folder_path()
        if os.path.exists(temp_folder_path):
            shutil.rmtree(temp_folder_path)
            return True
        else:
            return False

    def read_gpt_audio_path(self):
        audio_folder_path = self.read_temp_folder_path()

        audio_file_path = os.path.normpath(os.path.join(audio_folder_path, 'gpt_audio.wav'))

        return audio_file_path

    @staticmethod
    def get_expert_output_type(expert_mode):
        ai_output_type = ''

        if expert_mode == 'translator_mode':
            ai_output_type = 'translation'
        if expert_mode == 'writing_helper_mode':
            ai_output_type = 'modified text'
        if expert_mode == 'writer_mode':
            ai_output_type = 'written text'

        return ai_output_type

