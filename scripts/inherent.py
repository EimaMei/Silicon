class_source = input("Enter the class source: ")
class_inherent = input(f"Input the class that {class_source} will inherent: ")
source_name = input(f"Name of {class_source}'s object as a function argument: ")
inherent_name = input(f"Name of {class_inherent}'s object as a function argument: ")

#class_source   = "NSTextField"
#class_inherent = "NSWindow"
#source_name    = "field"
#inherent_name  = "window"

header_file = open("include/Silicon/silicon.h", "r+")
count = 0
inherented_properties, inherented_functions = [], []

get_info = 0
found = False

listt = header_file.readlines()
header_file = open("include/Silicon/silicon.h", "r+")

for line in header_file:
    parsed_line = line.split(" ")

    print(f"{count} - {get_info}")

    if (get_info != 0 and get_info != 4):
        count += 1

        if (line == "\n"):
            get_info += 1

            if (get_info == 1):
                inherented_properties.append(line)
            elif (get_info == 2):
                inherented_properties.append(line)
            elif (get_info > 2):
                get_info = 0

            continue
        elif (get_info == 1):
            line = line.replace(class_inherent, class_source)
            line = line.replace(inherent_name, source_name)
            inherented_properties.append(line)
            continue
        elif (get_info == 2):
            line = line.replace(class_inherent, class_source)
            line = line.replace(inherent_name, source_name)
            inherented_functions.append(line)
            continue

    if (line == "\n" and get_info == 4):
        for item in inherented_functions:
            listt.insert(count, item)
            count += 1
        break
    elif (get_info == 4):
        count +=1
        continue

    if (len(parsed_line) >= 4 and parsed_line[2] == class_inherent):
        print(f"L BOZO: {parsed_line}")
        get_info = 1
        count += 2


    if (len(parsed_line) >= 4 and parsed_line[2] == class_source):
        print(f"NUT BOZO: {parsed_line}")
        count += 2
        for item in inherented_properties:
            listt.insert(count, item)
            count += 1

        get_info = 4
        found = True
    count += 1

if (found == False):
    count -= 17
    listt.insert(count, f"\n/* ============ {class_source} class ============ */\n/* ====== {class_source} properties ====== */\n")
    count += 1
    i = 0
    for item in inherented_properties:
        if (i == 0):
            i += 1
            continue
        listt.insert(count, item)
        count += 1

    listt.insert(count, f"/* ====== {class_source} functions ====== */\n")
    count += 1

    i = 0
    for item in inherented_functions:
        if (i == 0):
            i += 1
            continue
        listt.insert(count, item)
        count += 1

    listt.insert(count, f"\n\n")

text = str()

for t in listt:
    text += t
header_file = open("include/Silicon/silicon.h", "w+")

header_file.write(text)

header_file.close()