src = []
src += 'RadarThreadTest.cpp'
src += '../main.cpp'

src += '../../Sources/Application/src/DCTCalculator.cpp'
src += '../../Sources/MessageSystem/src/Node.cpp'
src += '../../Sources/MessageSystem/src/MessageSender.cpp'
src += '../../Sources/MessageSystem/src/MessageProvider.cpp'
src += '../../Sources/RTOS/Threads/src/RadarThread.cpp'
src += '../../Sources/RTOS/src/Mutex.cpp'
src += '../../Sources/RTOS/src/TimeStamp.cpp'
src += '../../Sources/Drivers/src/PWMDrivenDevice.cpp'
src += '../../Sources/Drivers/src/HelpSignaler.cpp'
src += '../../Sources/Drivers/src/PWMDrivenDevice.cpp'

src += '../Stubs/src/semphr.c'
src += '../Stubs/src/RadarStub.cpp'

src += '../Mocks/src/TaskMock.cpp'
src += '../Mocks/src/MutexMock.cpp'
src += '../Mocks/src/MathMock.cpp'

inc = []
inc += include_directories('../../Sources/RTOS/Threads/inc')
inc += include_directories('../../Sources/MessageSystem/inc')
inc += include_directories('../../Sources/RTOS/inc')
inc += include_directories('../../Sources/Drivers/inc')
inc += include_directories('../../Sources/Wrappers/inc')
inc += include_directories('../../Sources/Application/inc')
inc += include_directories('../../Sources/RTOS/Threads/APIs')

inc += include_directories('../Stubs/inc')
inc += include_directories('../Mocks/inc')

dep = []
dep += dependency('gtest')
dep += dependency('gmock')

app = executable('ThreadsTest', src, include_directories : inc, dependencies : dep)

test('ThreadsTest', app)
