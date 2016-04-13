import os
import shutil
from xml.etree import ElementTree

del_dir = 'D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic\\__to_del'

for root, dirs, files in os.walk('D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic'):
    for fn in files:
        file_path = os.path.join(root, fn)
        f = open(file_path, 'rb')
        content = f.read()
        f.close()
        
        try:
            f_xml = ElementTree.fromstring(content)
        except:
            print content
            """if not file_path.endswith('.py'):
                del_file = os.path.join(del_dir, fn)
                shutil.move(file_path, del_file)"""
        
        """if len(content) < 40:
            print content, file_path
        if 'run-build.svg' in content and file_path.endswith('.py'):
            del_dir = 'D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic\\__to_del'
            print content"""