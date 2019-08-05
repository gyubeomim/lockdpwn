
#!/usr/bin/env pytohn
# -*- encoding=utf-8 -*-

from sympy.galgebra import *
from sympy import *
from sympy.abc import rho
import re # regex
import inspect, os

def word_replace(ls, params):
    #ls = re.sub(r'\b([a-zA-Z0-9_]*)\b\*\*\b([a-zA-Z0-9_])\b','pow(\g<1>,\g<2>)', ls)
    for symbol_vector, name in params:
        for i, elem in enumerate(symbol_vector):
            elem_name = elem.__repr__()
            ls = re.sub(r'\b%s\b'%elem_name, '%s[%d]'%(name,i), ls)
    #ls = re.sub(r'\btz_cp\b', 'pa[6]', ls)
    return ls

def ccodegen(eq, func_name, params):
    param_str = ''
    for symbol_vector, name in params:
        param_str += 'const double* %s, '%name
    header_code = 'void %s(%sdouble* output)'% (func_name, param_str)
    source_code = '%s{\n' % (header_code,)
    header_code += ';\n'
    tmp, result = cse(eq)
    for l in tmp:
        ls = ccode(l[1])
        ls = word_replace(ls, params)
        l = '\tdouble %s = %s;\n'%(l[0], ls)
        source_code += l
    result = result[0].tolist()
    for r, row in enumerate(result):
        for c, elem in enumerate(row):
            rows, cols = len(result), len(row)
            ls = ccode(elem)
            ls = word_replace(ls, params)
            idx = c*rows+r
            l = '\toutput[%d] = %s; //output[%d][%d]\n'%(idx, ls, r,c)
            source_code += l
    source_code += '}\n\n'
    return header_code, source_code

def ccodegen_scalar(eq, func_name, params):
    param_str = ''
    i = 0
    for symbol_vector, name in params:
        param_str += 'const double& %s'%name
        i += 1
        if i < len(params):
            param_str += ', '
    header_code = 'double %s(%s)'% (func_name, param_str)
    source_code = '%s{\n' % (header_code,)
    header_code += ';\n'
    ls = ccode(eq)
    ls = re.sub(r'\n','', ls)
    ls = re.sub(r' ','', ls)
    l = '\treturn %s;\n'%(ls)
    source_code += l
    source_code += '}\n\n'
    return header_code, source_code

def codegen_for_distortion():
    x, y = symbols('x, y')
    k1,k2,k3,k4 = symbols('k1,k2,k3,k4')
    xbar = Matrix([x, y]).reshape(2,1)
    r2 = x**2 + y**2
    r = sqrt(r2)
    th = atan(r)
    thd = th * (1.
            + k1*(th**2)
            + k2*(th**4)
            + k3*(th**6)
            + k4*(th**8)
            )
    xd = thd/r * x
    yd = thd/r * y
    xtilde = Matrix([xd, yd]).reshape(2,1)
    jac = xtilde.jacobian(xbar)
    '''
    modeling <<
    -----------------
    >> code generation
    '''
    header_code, source_code = '',''
    #header_code += '/*\n'
    #header_code += 'xtilde='+ pretty(xtilde.T, use_unicode=False)+'\n'
    #header_code += '*/\n'
    h, s = ccodegen(xtilde, 'distort', [(xbar,'xbar'),])
    source_code += s
    h, s = ccodegen(jac, 'jac_dxtilde_dxbar', [(xbar,'xbar'),])
    source_code += s
    print source_code


if __name__ == '__main__':
    codegen_for_distortion()
