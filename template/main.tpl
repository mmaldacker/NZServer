<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>
{% header = {title = "Main", abstract = "Some informative texts and tutorials"} %}
{# header #}

{% 
for a in article.get_all() do
%}
{{a.title}}
{%
end
%}

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
