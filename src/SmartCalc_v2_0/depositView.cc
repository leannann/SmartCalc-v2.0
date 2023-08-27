#include "depositView.h"

#include "depositModel.h"
#include "ui_deposit.h"

/**
 * @brief Конструктор класса Deposit.
 *
 * Создает объект класса Deposit и инициализирует пользовательский интерфейс.
 *
 * @param parent Указатель на родительский виджет (по умолчанию nullptr).
 *
 * @note Конструктор вызывается при создании объекта класса.
 */
s21::Deposit::Deposit(QWidget *parent) noexcept
    : QMainWindow(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
}

/**
 * @brief Деструктор класса Deposit.
 *
 * Удаляет объект класса Deposit и освобождает память, выделенную под
 * пользовательский интерфейс.
 */
s21::Deposit::~Deposit() { delete ui; }

/**
 * @brief Обработчик события клика по флажку.
 *
 * Устанавливает значение флага в зависимости от состояния флажка.
 *
 * @param checked Состояние флажка (выбран/не выбран).
 *
 * @note Функция вызывается при клике по флажку в пользовательском интерфейсе.
 *
 * @return void
 */
void s21::Deposit::on_flag_clicked(bool checked) noexcept {
  if (checked)
    flag = 1;
  else
    flag = 0;
}

/**
 * @brief Обработчик события клика по кнопке "Рассчитать".
 *
 * Извлекает данные из пользовательского интерфейса и передает их в функцию
 * расчета депозита.
 *
 * @note Функция вызывается при клике по кнопке "Рассчитать" в пользовательском
 * интерфейсе.
 *
 * @return void
 */
void s21::Deposit::on_calculate_clicked() noexcept {
  QString str_deposit = ui->input_deposit->text();
  double deposit_amount = str_deposit.toDouble();
  QString str_period = ui->input_period->text();
  double period = str_period.toDouble();
  QString str_rate = ui->input_rate->text();
  double rate = str_rate.toDouble();
  QString str_replenishment = ui->input_replenishment->text();
  double replenishment = str_replenishment.toDouble();
  QString str_withdrawals = ui->input_withdraw->text();
  double withdrawals = str_withdrawals.toDouble();
  QString str_taxrate = ui->input_taxrate->text();
  double tax_rate = str_taxrate.toDouble();

  double accrueds = 0;
  double depositEnd = 0;
  double tax_amount = 0;

  depositCalculator.deposit(deposit_amount, period, rate, tax_rate, accrueds,
                            depositEnd, tax_amount, flag, replenishment,
                            withdrawals, periodicity);

  QString p_outputCharges = QString::number(accrueds, 'g', 6);
  QString p_depositEnd = QString::number(depositEnd, 'g', 6);
  QString p_taxAmount = QString::number(tax_amount, 'g', 6);

  ui->input_percent->setText(p_outputCharges);
  ui->input_depositEnd->setText(p_depositEnd);
  ui->input_tax->setText(p_taxAmount);
}

/**
 * @brief Обработчик события выбора опции из выпадающего списка пополнения.
 *
 * Устанавливает значение переменной periodicity в зависимости от выбранной
 * опции.
 *
 * @param index Индекс выбранной опции в выпадающем списке.
 *
 * @note Функция вызывается при выборе опции из выпадающего списка пополнения в
 * пользовательском интерфейсе.
 *
 * @return void
 */
void s21::Deposit::on_dropdown_replemishment_activated(int index) noexcept {
  if (index == 0) periodicity = 0;
  if (index == 1) periodicity = 1;
  if (index == 2) periodicity = 3;
  if (index == 3) periodicity = 6;
  if (index == 4) periodicity = 12;
}

/**
 * @brief Обработчик события выбора опции из выпадающего списка снятия средств.
 *
 * Устанавливает значение переменной periodicity в зависимости от выбранной
 * опции.
 *
 * @param index Индекс выбранной опции в выпадающем списке.
 *
 * @note Функция вызывается при выборе опции из выпадающего списка снятия
 * средств в пользовательском интерфейсе.
 *
 * @return void
 */
void s21::Deposit::on_dropdown_withdraw_activated(int index) noexcept {
  if (index == 0) periodicity = 0;
  if (index == 1) periodicity = 1;
  if (index == 2) periodicity = 3;
  if (index == 3) periodicity = 6;
  if (index == 4) periodicity = 12;
}
