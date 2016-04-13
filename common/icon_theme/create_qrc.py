import os


def create_qrc():
    main = '<RCC>\n    <qresource prefix="/i">\n%s\n    </qresource>\n</RCC>'

    file_mask = '        <file alias=\"%s\">%s</file>'

    f = open('D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic.qrc', 'w')
    f.write(main)

    rcs = []

    cut_root = 'D:\\projects\\qtcreator\\igs-l4\\common\\'

    counter = 0

    for root, dirs, files in os.walk('D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic'):
        r = root.replace(cut_root, '')
        for fn in files:
            file_path = os.path.join(r, fn)
            rc_file = file_path.replace('\\', '/')
            alias = '%i_%s' % (counter, fn)
            rcs.append(file_mask % (alias, rc_file))
            counter += 1

    res = main % '\n'.join(rcs)

    f.write(res)

    f.close()

create_qrc()