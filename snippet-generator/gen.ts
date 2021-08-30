function getMostUsed(a) { var b = 0, c = 0, d = 0; for (var e in a) { var f = a[e], g = f[0], h = f[1]; (g > c || g === c && h > d) && (c = g, d = h, b = Number(e)) } return b } function getIndent(a) { if ("string" != typeof a) throw new TypeError("Expected a string"); var f, g, b = 0, c = 0, d = 0, e = {}; a.split(/\n/g).forEach(function (a) { if (a) { var h, i = a.match(INDENT_RE); i ? (h = i[0].length, i[1] ? c++ : b++) : h = 0; var j = h - d; d = h, j ? (g = j > 0, f = e[g ? j : -j], f ? f[0]++ : f = e[j] = [1, 0]) : f && (f[1] += Number(g)) } }); var i, h = getMostUsed(e); return h ? i = c >= b ? "space" : "tab" : (i = null), { amount: h, type: i } } var INDENT_RE = /^(?:( )+|\t+)/;

function repeating(a, b) { var c = ""; do 1 & a && (c += b), b += b; while (a >>= 1); return c }

export function getSnippet(lines: string[]): string[] {
    let indentAmount: number = 100;
    let indentType: string = '	';

    for (let i = 0; i < lines.length; i++) {
        const lineIndent = getIndent(lines[i]);
        if (lineIndent.type === 'space') {
            indentType = ' ';
        }
        if (lineIndent.amount) {
            indentAmount = indentAmount > lineIndent.amount ? lineIndent.amount : indentAmount;
        }
    }

    lines.map((line) => {
        const lineIndent = repeating(indentAmount, indentType);

        const match: RegExpMatchArray = line.match(new RegExp(`(${lineIndent})`, 'g'));

        const indent = match ? match.join('') : ''

        line = line.replace(new RegExp(lineIndent, 'g'), ' ');

        return indent + JSON.stringify(line);
    });
    return lines;
}
