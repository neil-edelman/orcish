# orcish\.c #

## Name Generator ##

 * [Description](#user-content-preamble)
 * [Function Summary](#user-content-summary)
 * [Function Definitions](#user-content-fn)
 * [License](#user-content-license)

## <a id = "user-content-preamble" name = "user-content-preamble">Description</a> ##

Orcish names originate or are inspired by [JRR Tolkien's Orcish](http://en.wikipedia.org/wiki/Languages_constructed_by_J._R._R._Tolkien)\.

 * Standard:  
   C89




## <a id = "user-content-summary" name = "user-content-summary">Function Summary</a> ##

<table>

<tr><th>Modifiers</th><th>Function Name</th><th>Argument List</th></tr>

<tr><td align = right>void</td><td><a href = "#user-content-fn-3a1dca27">orcish</a></td><td>name, name_size</td></tr>

<tr><td align = right>void</td><td><a href = "#user-content-fn-e3a93f48">orc_long</a></td><td>name, name_size, l</td></tr>

<tr><td align = right>void</td><td><a href = "#user-content-fn-3f3dd248">orc_ptr</a></td><td>name, name_size, p</td></tr>

<tr><td align = right>const char *</td><td><a href = "#user-content-fn-2ce9da4d">orcify</a></td><td>p</td></tr>

</table>



## <a id = "user-content-fn" name = "user-content-fn">Function Definitions</a> ##

### <a id = "user-content-fn-3a1dca27" name = "user-content-fn-3a1dca27">orcish</a> ###

<code>void <strong>orcish</strong>(char *const <em>name</em>, const size_t <em>name_size</em>)</code>

Fills `name` with a random Orcish name\. Potentially up to `name_size` \- 1, \(with a maximum of 255,\) then puts a null terminator\. Uses `rand` from `stdlib.h`\.

 * Parameter: _name_  
   A valid pointer to at least `name_size` characters\.
 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-e3a93f48" name = "user-content-fn-e3a93f48">orc_long</a> ###

<code>void <strong>orc_long</strong>(char *const <em>name</em>, const size_t <em>name_size</em>, const unsigned long <em>l</em>)</code>

Fills `name` with a deterministic Orcish name based on `l`, potentially up to `name_size` \- 1, \(with a maximum of 255,\) then puts a null terminator\.

 * Parameter: _name_  
   A valid pointer to at least `name_size` characters\.
 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-3f3dd248" name = "user-content-fn-3f3dd248">orc_ptr</a> ###

<code>void <strong>orc_ptr</strong>(char *const <em>name</em>, const size_t <em>name_size</em>, const void *const <em>p</em>)</code>

Fills `name` with a deterministic Orcish name based on `p`, or if `p` is null, then "null"\. Potentially up to `name_size` \- 1, \(with a maximum of 255,\) then puts a null terminator\.

 * Parameter: _name_  
   A valid pointer to at least `name_size` characters\.
 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-2ce9da4d" name = "user-content-fn-2ce9da4d">orcify</a> ###

<code>const char *<strong>orcify</strong>(const void *const <em>p</em>)</code>

Call [orc_ptr](#user-content-fn-3f3dd248) with `p` with default values and a small temporary buffer\.

 * Return:  
   A temporary string; can handle four names at a time\.






## <a id = "user-content-license" name = "user-content-license">License</a> ##

2014 Neil Edelman, distributed under the terms of the [MIT License](https://opensource.org/licenses/MIT)\. Contains some syllables from [SMAUG](http://www.smaug.org/), which is a derivative of [Merc](http://dikumud.com/Children/merc2.asp), and [DikuMud](http://dikumud.com/); used under fair\-use\. Contains [MurmurHash](https://github.com/aappleby/smhasher)\-derived code, placed in public domain by Austin Appleby\.



