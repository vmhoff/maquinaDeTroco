using CLI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ChangeMachineApp
{
    /// <summary>
    /// Interação lógica para MainWindow.xam
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Pagar_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int cash = (int)(double.Parse(tbValor.GetLineText(0).Replace(',', '.')));
                int[] coinValues = { 5, 10, 25, 50, 100, 0 };
                int[] coinCount = { 0, 0, 0, 0, 0, 0 };
                int coinsLength = 0;

                ChangeMachineWrapper changeMachineWrapper = new ChangeMachineWrapper();
                changeMachineWrapper.PayChange(cash, coinValues, coinCount, ref coinsLength);

                lbRes100.Content = coinCount[4];
                lbRes50.Content = coinCount[3];
                lbRes25.Content = coinCount[2];
                lbRes10.Content = coinCount[1];
                lbRes5.Content = coinCount[0];

                lbStatus.Content = "Pagamento finalizado";
            }
            catch(Exception ex)
            {
                lbRes100.Content = 0;
                lbRes50.Content = 0;
                lbRes25.Content = 0;
                lbRes10.Content = 0;
                lbRes5.Content = 0;
                lbStatus.Content = "Operação não pode ser concluída";
            }
        }

        private void Abastecer_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int abast100 = int.Parse(tbAbast100.GetLineText(0));
                int abast50 = int.Parse(tbAbast50.GetLineText(0));
                int abast25 = int.Parse(tbAbast25.GetLineText(0));
                int abast10 = int.Parse(tbAbast10.GetLineText(0));
                int abast5 = int.Parse(tbAbast5.GetLineText(0));
                int[] coinValues = { 5, 10, 25, 50, 100, 0 };
                int[] coinCount = { abast5, abast10, abast25, abast50, abast100, 0 };
                int coinsLength = 5;

                ChangeMachineWrapper changeMachineWrapper = new ChangeMachineWrapper();
                changeMachineWrapper.EndExchange(1, coinValues, coinCount, coinsLength);

                lbStatus.Content = "Abastecimento finalizado";
            }
            catch (Exception ex)
            {
                lbStatus.Content = "Operação não pode ser concluída";
            }   
        }

        private void Inicializar_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int[] coinValues = { 5, 10, 25, 50, 100, 0 };
                int[] coinCount = { 0, 0, 0, 0, 0, 0 };
                int coinsLength = 5;

                ChangeMachineWrapper changeMachineWrapper = new ChangeMachineWrapper();
                changeMachineWrapper.EndExchange(0, coinValues, coinCount, coinsLength);

                lbStatus.Content = "Inicialização finalizada";
            }
            catch (Exception ex)
            {
                lbStatus.Content = "Operação não pode ser concluída";
            }
        }

        private void Retirar_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int retir100 = int.Parse(tbRetir100.GetLineText(0));
                int retir50 = int.Parse(tbRetir50.GetLineText(0));
                int retir25 = int.Parse(tbRetir25.GetLineText(0));
                int retir10 = int.Parse(tbRetir10.GetLineText(0));
                int retir5 = int.Parse(tbRetir5.GetLineText(0));
                int[] coinValues = { 5, 10, 25, 50, 100, 0 };
                int[] coinCount = { retir5, retir10, retir25, retir50, retir100, 0 };
                int coinsLength = 5;

                ChangeMachineWrapper changeMachineWrapper = new ChangeMachineWrapper();
                changeMachineWrapper.CashOut(coinValues, coinCount, coinsLength);

                lbStatus.Content = "Retirada finalizada";
            }
            catch (Exception ex)
            {
                lbStatus.Content = "Operação não pode ser concluída";
            }
        }

        private void Verificar_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int[] coinValues = { 5, 10, 25, 50, 100, 0 };
                int[] coinCount = { 0, 0, 0, 0, 0, 0 };
                int coinsLength = 0;

                ChangeMachineWrapper changeMachineWrapper = new ChangeMachineWrapper();
                changeMachineWrapper.GetCountCoinList(coinValues, coinCount, ref coinsLength);

                lbVer100.Content = coinCount[4];
                lbVer50.Content = coinCount[3];
                lbVer25.Content = coinCount[2];
                lbVer10.Content = coinCount[1];
                lbVer5.Content = coinCount[0];

                lbStatus.Content = "Verificação finalizada";
            }
            catch (Exception ex)
            {
                lbRes100.Content = "?";
                lbRes50.Content = "?";
                lbRes25.Content = "?";
                lbRes10.Content = "?";
                lbRes5.Content = "?";
                lbStatus.Content = "Operação não pode ser concluída";
            }

        }
    }
}
