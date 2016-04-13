import os


def create_qrc():
    main = '<RCC>\n    <qresource prefix="/breeze_classic">\n%s\n    </qresource>\n</RCC>'

    # file_mask = '        <file alias=\"%s\">%s</file>'
    file_mask = '        <file>%s</file>'

    cut_root = 'D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic\\'

    # counter = 0

    qrc_root = 'D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic'

    for root, dirs, files in os.walk('D:\\projects\\qtcreator\\igs-l4\\common\\icon_theme\\breeze_classic'):
        if not files:
            continue

        rcs = []

        r = root.replace(cut_root, '')

        qrc_file_name = os.path.join(qrc_root, r.replace('\\', '_') + '.qrc')
        print qrc_file_name

        f = open(qrc_file_name, 'w')

        for fn in files:
            file_path = os.path.join(r, fn)
            rc_file = file_path.replace('\\', '/')
            # alias = '%i_%s' % (counter, fn)
            # rcs.append(file_mask % (alias, rc_file))
            rcs.append(file_mask % rc_file)
            # counter += 1

        res = main % '\n'.join(rcs)

        f.write(res)

        f.close()

create_qrc()