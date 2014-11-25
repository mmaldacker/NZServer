<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>
{% header = {title = "Main", abstract = "Some informative texts and tutorials"} %}
{# header #}

{% 
it = article.get_all()
while true do
  local a = it:get()
  if a == nil then break end
%}
{{a.title}}
{%
end
%}

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
