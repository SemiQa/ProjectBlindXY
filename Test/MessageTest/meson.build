src = []
src += 'MessageTest.cpp'
src += '../main.cpp'

src += '../../Sources/MessageSystem/src/Message.cpp'

inc = []
inc += include_directories('../../Sources/MessageSystem/inc')

dep = []
dep += dependency('gtest')
dep += dependency('gmock')

app = executable('MessageTest', src, include_directories : inc, dependencies : dep)

test('MessageTest', app)