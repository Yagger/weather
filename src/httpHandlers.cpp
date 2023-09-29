#include <common.h>

String SendHTML(char cityID[255])
{
    char s[3000];
    sprintf(s, PSTR("<!DOCTYPE HTML><html><head><meta charset=\"UTF-8\"><title>Main</title><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><script src=\"https://cdn.tailwindcss.com\"></script><script src=\"https://code.jquery.com/jquery-3.7.0.min.js\"></script><script src=\"https://code.jquery.com/ui/1.13.2/jquery-ui.min.js\"></script><style>.ui-autocomplete{background-color:#fff}.ui-helper-hidden-accessible{display:none}</style><script>class MyInput extends HTMLElement{constructor(){super()}connectedCallback(){this.innerHTML=`<label for=\"${this.getAttribute(\"name\")}\" class=\"block mb-2 text-sm font-medium text-gray-900\">${this.getAttribute(\"label\")}</label><input type=\"${this.getAttribute(\"type\")}\" id=\"${this.getAttribute(\"name\")}\" name=\"${this.getAttribute(\"name\")}\" class=\"bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5\" placeholder=\"${this.getAttribute(\"placeholder\")}\" value=\"${this.getAttribute(\"value\")}\">`}}customElements.define(\"my-input\",MyInput);class MyButton extends HTMLElement{constructor(){super()}connectedCallback(){var t=this.getAttribute(\"type\");null===t&&(type=\"button\"),this.innerHTML=`<button type=\"${t}\" class=\"bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded\">${this.getAttribute(\"label\")}</button>`}}function validateForm(t){var e=document.forms.myForm.brightness.value;let n=document.forms.myForm.citID.value;return\"\"===e||\"\"===n?alert(\"All fields must be filled\"):$.ajax({url:\"http://misc.bux.ee/coordinates/\"+n,type:\"get\"}).done(()=>{t.target.submit()}).fail(t=>(404===t.status?alert(`City code ${n} not found, please select from the list of suggestions`):alert(`Something went wrong (${t.status})`),!1)),!1}customElements.define(\"my-button\",MyButton),$(function(){$(\"#cityID\").autocomplete({source:function(t,e){2<t.term.length&&$.ajax({url:\"http://misc.bux.ee/cities/ids?filter=\"+t.term,type:\"get\"}).done(function(t){e(t)}).fail(function(){e([])})}})})</script></head><body class=\"p-5\"><form name=\"myForm\" method=\"POST\" action=\"\" onsubmit=\"return validateForm(event)\"><div class=\"mb-6\"><my-input type=\"text\" name=\"cityID\" label=\"City name: \" placeholder=\"Tallinn_EE\" value=\"%s\"></my-input></div><my-button type=\"submit\" label=\"Submit\"></my-button></form></body></html>"), cityID);
    return String(s);
}

void handleGet()
{
    server.send(200, "text/html", SendHTML(conf.cityID));
}

void handlePost()
{
    // String brightnessString = server.arg("brightness");
    // if (brightnessString == "")
    // {
    //     server.send(400, "text/plain", "POST payload missing `brightness` parameter");
    //     return;
    // }
    // int brightness = brightnessString.toInt();
    String cityID = server.arg("cityID");
    if (cityID == "")
    {
        server.send(400, "text/plain", "POST payload missing `cityID` parameter");
        return;
    }
    // conf.brightness = brightness;
    cityID.toCharArray(conf.cityID, 255);
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(0, conf);
    EEPROM.end();
    server.send(200, "text/html", SendHTML(conf.cityID));
    showConfigScreen = false;
}

void handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}