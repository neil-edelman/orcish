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

<tr><td align = right>void</td><td><a href = "#user-content-fn-9f378872">orcish_ptr</a></td><td>name, name_size, p</td></tr>

<tr><td align = right>void</td><td><a href = "#user-content-fn-d7a266c9">orcish_int</a></td><td>name, name_size, i</td></tr>

<tr><td align = right>void</td><td><a href = "#user-content-fn-d9cde336">orcish_long</a></td><td>name, name_size, l</td></tr>

<tr><td align = right>const char *</td><td><a href = "#user-content-fn-a01df6a5">orc</a></td><td>p</td></tr>

<tr><td align = right>const char *</td><td><a href = "#user-content-fn-6b4ff17f">orc_int</a></td><td>i</td></tr>

<tr><td align = right>const char *</td><td><a href = "#user-content-fn-e3a93f48">orc_long</a></td><td>l</td></tr>

</table>



## <a id = "user-content-fn" name = "user-content-fn">Function Definitions</a> ##

### <a id = "user-content-fn-3a1dca27" name = "user-content-fn-3a1dca27">orcish</a> ###

<code>void <strong>orcish</strong>(char *const <em>name</em>, const size_t <em>name_size</em>)</code>

Fills `name` with a random Orcish name\. Potentially up to `name_size` \- 1, then puts a null terminator\. Uses `rand` from `stdlib.h`\.

 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-9f378872" name = "user-content-fn-9f378872">orcish_ptr</a> ###

<code>void <strong>orcish_ptr</strong>(char *const <em>name</em>, const size_t <em>name_size</em>, const void *const <em>p</em>)</code>

Fills `name` with a deterministic Orcish name based on `p`\. Potentially up to `name_size` \- 1, then puts a null terminator\.

 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-d7a266c9" name = "user-content-fn-d7a266c9">orcish_int</a> ###

<code>void <strong>orcish_int</strong>(char *const <em>name</em>, const size_t <em>name_size</em>, const unsigned <em>i</em>)</code>

Fills `name` with a deterministic Orcish name based on `i`\. Potentially up to `name_size` \- 1, then puts a null terminator\.

 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-d9cde336" name = "user-content-fn-d9cde336">orcish_long</a> ###

<code>void <strong>orcish_long</strong>(char *const <em>name</em>, const size_t <em>name_size</em>, const unsigned long <em>l</em>)</code>

Fills `name` with a deterministic Orcish name based on `l`\. Potentially up to `name_size` \- 1, then puts a null terminator\.

 * Parameter: _name\_size_  
   If zero, does nothing\.




### <a id = "user-content-fn-a01df6a5" name = "user-content-fn-a01df6a5">orc</a> ###

<code>const char *<strong>orc</strong>(const void *const <em>p</em>)</code>

Fills a static buffer of up to four names with a deterministic Orcish name based on `p` with [orcish_ptr](#user-content-fn-9f378872)\.



### <a id = "user-content-fn-6b4ff17f" name = "user-content-fn-6b4ff17f">orc_int</a> ###

<code>const char *<strong>orc_int</strong>(const unsigned <em>i</em>)</code>

Fills a static buffer of up to four names with a deterministic Orcish name based on `i`\.



### <a id = "user-content-fn-e3a93f48" name = "user-content-fn-e3a93f48">orc_long</a> ###

<code>const char *<strong>orc_long</strong>(const unsigned long <em>l</em>)</code>

Fills a static buffer of up to four names with a deterministic Orcish name based on `l`\.





## <a id = "user-content-license" name = "user-content-license">License</a> ##

2014, 2021 Neil Edelman, distributed under the terms of the [MIT License](https://opensource.org/licenses/MIT)\. Contains some syllables from [SMAUG](http://www.smaug.org/), which is a derivative of [Merc](http://dikumud.com/Children/merc2.asp), and [DikuMud](http://dikumud.com/); used under fair\-use\. Contains [MurmurHash](https://github.com/aappleby/smhasher)\-derived code, placed in public domain by Austin Appleby\.



