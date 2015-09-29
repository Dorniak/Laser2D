object Principal: TPrincipal
  Left = 404
  Top = 167
  Width = 1117
  Height = 570
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = menuPrincipal
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 160
    Top = 312
    Width = 13
    Height = 13
    Caption = 'Hz'
  end
  object Label2: TLabel
    Left = 152
    Top = 352
    Width = 170
    Height = 13
    Caption = 'voltios. Distancia de reconocimiento'
  end
  object textMemo: TMemo
    Left = 8
    Top = 64
    Width = 369
    Height = 209
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'Controlador Laser Sick 5.0')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object panel: TPanel
    Left = 532
    Top = 42
    Width = 500
    Height = 400
    Color = clSkyBlue
    TabOrder = 1
    object imagenPanel: TImage
      Left = 0
      Top = 0
      Width = 500
      Height = 400
      Center = True
      Transparent = True
    end
  end
  object CheckBox1: TCheckBox
    Left = 536
    Top = 16
    Width = 97
    Height = 17
    Caption = 'Timer Pantalla'
    TabOrder = 2
    OnClick = CheckBox1Click
  end
  object CheckBox2: TCheckBox
    Left = 8
    Top = 304
    Width = 97
    Height = 17
    Caption = 'GPS Conectado'
    TabOrder = 3
  end
  object CheckBox3: TCheckBox
    Left = 8
    Top = 328
    Width = 97
    Height = 17
    Caption = 'Advantech'
    TabOrder = 4
  end
  object CheckBox4: TCheckBox
    Left = 8
    Top = 352
    Width = 97
    Height = 17
    Caption = 'CAN'
    TabOrder = 5
  end
  object Edit1: TEdit
    Left = 120
    Top = 304
    Width = 33
    Height = 21
    TabOrder = 6
    Text = '100'
  end
  object Edit2: TEdit
    Left = 1000
    Top = 448
    Width = 17
    Height = 21
    Enabled = False
    TabOrder = 7
    Text = '0'
  end
  object Edit3: TEdit
    Left = 120
    Top = 344
    Width = 25
    Height = 21
    TabOrder = 8
    Text = '1'
  end
  object Memo1: TMemo
    Left = 384
    Top = 64
    Width = 137
    Height = 377
    Lines.Strings = (
      'Memo1')
    TabOrder = 9
  end
  object Button1: TButton
    Left = 16
    Top = 384
    Width = 145
    Height = 57
    Caption = 'Velocidad'
    TabOrder = 10
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 384
    Width = 145
    Height = 57
    Caption = 'Volante'
    TabOrder = 11
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 16
    Top = 448
    Width = 297
    Height = 57
    Caption = 'Freno'
    TabOrder = 12
    OnClick = Button3Click
  end
  object menuPrincipal: TMainMenu
    Left = 120
    Top = 16
    object menuLaser: TMenuItem
      Caption = 'Laser'
      object ConectarPuerto: TMenuItem
        Caption = 'Conectar Puerto'
        OnClick = ConectarPuertoClick
      end
      object ConexionRapida1: TMenuItem
        Caption = 'Conexion Rapida'
        OnClick = ConexionRapida1Click
      end
      object nPuertoLaser: TMenuItem
        Caption = 'N'#186' Puerto'
        object laserPuerto1: TMenuItem
          Tag = 1
          Caption = '1'
          OnClick = laserPuerto1Click
        end
        object laserPuerto2: TMenuItem
          Tag = 2
          Caption = '2'
          OnClick = laserPuerto2Click
        end
        object laserPuerto3: TMenuItem
          Tag = 3
          Caption = '3'
          OnClick = laserPuerto3Click
        end
        object laserPuerto4: TMenuItem
          Tag = 4
          Caption = '4'
          OnClick = laserPuerto4Click
        end
        object laserPuerto5: TMenuItem
          Tag = 5
          Caption = '5'
          OnClick = laserPuerto5Click
        end
        object laserPuerto6: TMenuItem
          Tag = 6
          Caption = '6'
          OnClick = laserPuerto6Click
        end
      end
      object nVelocidadLaser: TMenuItem
        Caption = 'Velocidad'
        object vLaser1200: TMenuItem
          Tag = 1200
          Caption = '1200'
          OnClick = vLaser1200Click
        end
        object vLaser2400: TMenuItem
          Tag = 2400
          Caption = '2400'
          OnClick = vLaser2400Click
        end
        object vLaser4800: TMenuItem
          Tag = 4800
          Caption = '4800'
          OnClick = vLaser4800Click
        end
        object vLaser9600: TMenuItem
          Tag = 9600
          Caption = '9600'
          OnClick = vLaser9600Click
        end
        object vLaser19200: TMenuItem
          Tag = 19200
          Caption = '19200'
          OnClick = vLaser19200Click
        end
        object vLaser38400: TMenuItem
          Tag = 38400
          Caption = '38400'
          OnClick = vLaser38400Click
        end
        object vLaser57600: TMenuItem
          Tag = 57600
          Caption = '57600'
          OnClick = vLaser57600Click
        end
        object vLaser115200: TMenuItem
          Tag = 115200
          Caption = '115200'
          OnClick = vLaser115200Click
        end
      end
      object botonInicializar: TMenuItem
        Caption = 'Inicializar'
        OnClick = botonInicializarClick
      end
      object botonECO: TMenuItem
        Caption = 'ECO'
        OnClick = botonECOClick
      end
      object botonApertura: TMenuItem
        Caption = 'Apertura'
        object Confi60Grados: TMenuItem
          Caption = '60'#186
          OnClick = Confi60GradosClick
        end
        object Confi180Grados: TMenuItem
          Caption = '180'#186
          OnClick = Confi180GradosClick
        end
      end
      object botonFrecuencia: TMenuItem
        Caption = 'Frecuencia'
        object confi10Hz: TMenuItem
          Tag = 10
          Caption = '10 Hz'
          OnClick = confi10HzClick
        end
        object confi5Hz: TMenuItem
          Tag = 5
          Caption = '5 Hz'
          OnClick = confi5HzClick
        end
      end
      object botonResolucion: TMenuItem
        Caption = 'Resoluci'#243'n'
        object confi1Grado: TMenuItem
          Caption = '1'#186
          OnClick = confi1GradoClick
        end
        object confi05Grado: TMenuItem
          Caption = '0.5'#186
          OnClick = confi05GradoClick
        end
        object confi025Grado: TMenuItem
          Caption = '0.25'#186
          OnClick = confi025GradoClick
        end
        object confi0125Grado: TMenuItem
          Caption = '0.125'#186
          OnClick = confi0125GradoClick
        end
      end
      object Rotar: TMenuItem
        Caption = 'Rotar'
        OnClick = RotarClick
      end
      object Halt: TMenuItem
        Caption = 'Halt'
        OnClick = HaltClick
      end
    end
    object menuGPS: TMenuItem
      Caption = 'GPS'
      object conectarGPS: TMenuItem
        Caption = 'Conectar GPS'
        OnClick = conectarGPSClick
      end
      object nPuertoGPS: TMenuItem
        Caption = 'N'#186' Puerto'
        object gpsPuerto1: TMenuItem
          Tag = 1
          Caption = '1'
          OnClick = gpsPuerto1Click
        end
        object gpsPuerto2: TMenuItem
          Tag = 2
          Caption = '2'
          OnClick = gpsPuerto2Click
        end
        object gpsPuerto3: TMenuItem
          Tag = 3
          Caption = '3'
          OnClick = gpsPuerto3Click
        end
        object gpsPuerto4: TMenuItem
          Tag = 4
          Caption = '4'
          OnClick = gpsPuerto4Click
        end
        object gpsPuerto5: TMenuItem
          Tag = 5
          Caption = '5'
          OnClick = gpsPuerto5Click
        end
        object gpsPuerto6: TMenuItem
          Tag = 6
          Caption = '6'
          OnClick = gpsPuerto6Click
        end
      end
      object nVelocidadGPS: TMenuItem
        Caption = 'Velocidad'
        object vGPS1200: TMenuItem
          Tag = 1200
          Caption = '1200'
          OnClick = vGPS1200Click
        end
        object vGPS2400: TMenuItem
          Tag = 2400
          Caption = '2400'
          OnClick = vGPS2400Click
        end
        object vGPS4800: TMenuItem
          Tag = 4800
          Caption = '4800'
          OnClick = vGPS4800Click
        end
        object vGPS9600: TMenuItem
          Tag = 9600
          Caption = '9600'
          OnClick = vGPS9600Click
        end
        object vGPS19200: TMenuItem
          Tag = 19200
          Caption = '19200'
          OnClick = vGPS19200Click
        end
        object vGPS38400: TMenuItem
          Tag = 38400
          Caption = '38400'
          OnClick = vGPS38400Click
        end
        object vGPS57600: TMenuItem
          Tag = 57600
          Caption = '57600'
          OnClick = vGPS57600Click
        end
        object vGPS115200: TMenuItem
          Tag = 115200
          Caption = '115200'
          OnClick = vGPS115200Click
        end
      end
    end
    object otras: TMenuItem
      Caption = '"Otras comunicaciones"'
      object tarjetaAdquisicion: TMenuItem
        Caption = 'Tarjetas Adquisici'#243'n'
        OnClick = tarjetaAdquisicionClick
      end
      object can: TMenuItem
        Caption = 'CAN'
        OnClick = canClick
      end
    end
    object threadLectura: TMenuItem
      Caption = 'Lectura'
      object IniciarLecturaLaser: TMenuItem
        Caption = 'Iniciar'
        OnClick = IniciarLecturaLaserClick
      end
      object PararLecturaLaser: TMenuItem
        Caption = 'Parar'
        OnClick = PararLecturaLaserClick
      end
    end
  end
  object Temporizador: TTimer
    Enabled = False
    OnTimer = TemporizadorTimer
    Left = 24
    Top = 16
  end
  object timerPantalla: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = timerPantallaTimer
    Left = 72
    Top = 16
  end
  object TimerGPS: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerGPSTimer
    Left = 184
    Top = 304
  end
  object ClientSocket1: TClientSocket
    Active = True
    ClientType = ctNonBlocking
    Host = '192.168.0.1'
    Port = 2328
    OnConnect = ClientSocket1Connect
    OnError = ClientSocket1Error
    Left = 176
    Top = 16
  end
  object ClientSocket2: TClientSocket
    Active = True
    ClientType = ctNonBlocking
    Host = '192.168.0.1'
    Port = 2329
    OnConnect = ClientSocket2Connect
    OnError = ClientSocket2Error
    Left = 208
    Top = 16
  end
  object ClientSocket3: TClientSocket
    Active = True
    ClientType = ctNonBlocking
    Host = '192.168.0.1'
    Port = 2330
    OnConnect = ClientSocket3Connect
    OnError = ClientSocket3Error
    Left = 240
    Top = 16
  end
end