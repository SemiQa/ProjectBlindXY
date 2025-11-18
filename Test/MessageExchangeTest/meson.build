src = []
src += 'MessageExchangeTest.cpp'
src += '../main.cpp'

src += '../../Sources/MessageSystem/src/Message.cpp'
src += '../../Sources/MessageSystem/src/Node.cpp'
src += '../../Sources/MessageSystem/src/MessageProvider.cpp'
src += '../../Sources/MessageSystem/src/MessageSender.cpp'
src += '../../Sources/RTOS/Threads/src/LoopbackThread.cpp'
src += '../../Sources/RTOS/Threads/src/USBThread.cpp'
src += '../../Sources/RTOS/src/Mutex.cpp'


src += '../Stubs/src/cy_retarget_io.c'
src += '../Stubs/src/semphr.c'

src += '../Mocks/src/TaskMock.cpp'
src += '../Mocks/src/UartMock.cpp'
src += '../Mocks/src/MutexMock.cpp'

inc = []
inc += include_directories('../../Sources/MessageSystem/inc')
inc += include_directories('../../Sources/RTOS/Threads/inc')
inc += include_directories('../../Sources/RTOS/inc')
inc += include_directories('../../bsps/TARGET_APP_CY8CKIT-062S2-AI/config/GeneratedSource')

inc += include_directories('../Stubs/inc')
inc += include_directories('../Mocks/inc')

dep = []
dep += dependency('gtest')
dep += dependency('gmock')

app = executable('MessageExchangeTest', src, include_directories : inc, dependencies : dep)

test('MessageExchangeTest', app)