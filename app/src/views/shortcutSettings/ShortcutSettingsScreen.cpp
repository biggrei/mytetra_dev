#include "ShortcutSettingsScreen.h"


ShortcutSettingsScreen::ShortcutSettingsScreen(QWidget *parent) : QDialog(parent)
{
    // Инициализируется контроллер списка записей
    shortcutSettingsController=new ShortcutSettingsController(this);
    shortcutSettingsController->setObjectName("shortcutSettingsController");
    shortcutSettingsController->init();

    setupUI();
    setupSignals();
    assembly();
}


ShortcutSettingsScreen::~ShortcutSettingsScreen()
{

}


void ShortcutSettingsScreen::setupUI()
{
    // Создание различных кнопок
    buttonGrabShortcut=new QPushButton(tr("Grab shortcut"), this);
    buttonResetShortcutToDefault=new QPushButton(tr("Reset shortcut to default"), this);
    buttonResetAllShortcutsToDefault=new QPushButton(tr("Reset all shortcuts to default"), this);

    shortcutBox=new QGroupBox(this);
    shortcutBox->setTitle(tr("Shortcut settings"));

    commandLabel=new QLabel(tr("Command:"), this);
    commandValueLabel=new QLabel(this);

    desctiptionLabel=new QLabel(tr("Description:"), this);
    desctiptionValueLabel=new QLabel(this);

    shortcutLabel=new QLabel(tr("Key binding:"), this);
    shortcutValueLine=new QLineEdit(this);

    // Создание набора диалоговых кнопок
    dialogButtonBox=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}


void ShortcutSettingsScreen::setupSignals()
{
    // Обработка кнопки OK
    connect(dialogButtonBox, &QDialogButtonBox::accepted,
            shortcutSettingsController, &ShortcutSettingsController::applyChanges); // Применение изменений
    connect(dialogButtonBox, &QDialogButtonBox::accepted,
            this, &ShortcutSettingsScreen::close); // Закрытие текущего окна

    // Обработка кнопки Cancel
    connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &ShortcutSettingsScreen::close);
}


void ShortcutSettingsScreen::assembly()
{
    // Слой с полем сочетания клавиш, кнопками Grab и Reset to default
    shortcutLineLayout=new QHBoxLayout(this);
    shortcutLineLayout->addWidget(shortcutValueLine);
    shortcutLineLayout->addWidget(buttonGrabShortcut);
    shortcutLineLayout->addWidget(buttonResetShortcutToDefault);

    // Слой внутри объединяющего прямоугольника настройки шортката
    shortcutLayout=new QGridLayout(this);
    shortcutLayout->addWidget(commandLabel, 0, 0);
    shortcutLayout->addWidget(commandValueLabel, 0, 1);
    shortcutLayout->addWidget(desctiptionLabel, 1, 0);
    shortcutLayout->addWidget(desctiptionValueLabel, 1, 1);
    shortcutLayout->addWidget(shortcutLabel, 2, 0);
    shortcutLayout->addLayout(shortcutLineLayout, 2, 1);

    shortcutBox->setLayout(shortcutLayout);

    screenLayout=new QVBoxLayout(this);
    screenLayout->addWidget(shortcutSettingsController->getView());
    screenLayout->addWidget(shortcutBox);
    screenLayout->addWidget(buttonResetAllShortcutsToDefault);
    screenLayout->addWidget(dialogButtonBox);

    setLayout(screenLayout);
}