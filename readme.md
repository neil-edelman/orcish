# orcish\.c #

## Random Name Generator ##

 * [Description](#user-content-preamble)
 * [Function Summary](#user-content-summary)
 * [Function Definitions](#user-content-fn)
 * [License](#user-content-license)

## <a id = "user-content-preamble" name = "user-content-preamble">Description</a> ##

Orcish names are gathered off the Internet, SMAUG1\.8, made up myself, _etc_\. They originate or are inspired by [JRR Tolkien's Orcish](http://en.wikipedia.org/wiki/Languages_constructed_by_J._R._R._Tolkien)\.

 * Standard:  
   C89




## <a id = "user-content-summary" name = "user-content-summary">Function Summary</a> ##

<table>

<tr><th>Modifiers</th><th>Function Name</th><th>Argument List</th></tr>

<tr><td align = right>void</td><td><a href = "#user-content-fn-3a1dca27">orcish</a></td><td>name, name_size</td></tr>

</table>



## <a id = "user-content-fn" name = "user-content-fn">Function Definitions</a> ##

### <a id = "user-content-fn-3a1dca27" name = "user-content-fn-3a1dca27">orcish</a> ###

<code>void <strong>orcish</strong>(char *const <em>name</em>, size_t <em>name_size</em>)</code>

Fills `name` with a random Orcish name\. Potentially up to `name_size` \- 1, then puts a null terminator\. Uses `rand` from `stdlib.h`\.

 * Parameter: _name\_size_  
   If zero, does nothing\.






## <a id = "user-content-license" name = "user-content-license">License</a> ##

2014 Neil Edelman, distributed under the terms of the [MIT License](https://opensource.org/licenses/MIT)\. Contains some syllables from [SMAUG](http://www.smaug.org/), which is a derivative of [Merc](http://dikumud.com/Children/merc2.asp), and [DikuMud](http://dikumud.com/); used under fair\-use\.



