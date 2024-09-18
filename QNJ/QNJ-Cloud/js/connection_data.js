const QNJCLIENTDATASECTIONID = document.getElementById("QNJ-CLIENT-DATA-SECTION-ID");
const QNJCLIENTDATASECTIONSTAT = document.getElementById("QNJ-CLIENT-DATA-SECTION-STAT");
const QNJCLIENTDATASECTIONRADDR = document.getElementById("QNJ-CLIENT-DATA-SECTION-RADDR");
const QNJCLIENTDATASECTIONIPADDR = document.getElementById("QNJ-CLIENT-DATA-SECTION-IPADDR");
const QNJCLIENTDATASECTIONOS = document.getElementById("QNJ-CLIENT-DATA-SECTION-OS");
const QNJCLIENTDATASECTIONOSREL = document.getElementById("QNJ-CLIENT-DATA-SECTION-OSREL");
const QNJCLIENTDATASECTIONARCH = document.getElementById("QNJ-CLIENT-DATA-SECTION-ARCH");
const QNJCLIENTDATASECTIONDEL = document.getElementById("QNJ-CLIENT-DATA-SECTION-DEL");

const components_id = document.querySelectorAll(".component-0-0");
const components_stat = document.querySelectorAll(".component-0-1");
const components_raddr = document.querySelectorAll(".component-0-2");
const components_ipaddr = document.querySelectorAll(".component-0-3");
const components_os = document.querySelectorAll(".component-0-4");
const components_osrel = document.querySelectorAll(".component-0-5");
const components_arch = document.querySelectorAll(".component-0-6");

const QNJDELETECLIENTIDCLASS = document.querySelectorAll(".QNJ-DELETE-CLIENT-ID-CLASS");

components_id.forEach(component => {
    QNJCLIENTDATASECTIONID.appendChild(component);
});

components_stat.forEach(component => {
    QNJCLIENTDATASECTIONSTAT.appendChild(component);
});

components_raddr.forEach(component => {
    QNJCLIENTDATASECTIONRADDR.appendChild(component);
});

components_ipaddr.forEach(component => {
    QNJCLIENTDATASECTIONIPADDR.appendChild(component);
});

components_os.forEach(component => {
    QNJCLIENTDATASECTIONOS.appendChild(component);
});

components_osrel.forEach(component => {
    QNJCLIENTDATASECTIONOSREL.appendChild(component);
});

components_arch.forEach(component => {
    QNJCLIENTDATASECTIONARCH.appendChild(component);
});

QNJDELETECLIENTIDCLASS.forEach(component => {
    QNJCLIENTDATASECTIONDEL.appendChild(component);
});